#include "rungekuttaintegrator.h"
#include "forcesimulator.h"
#include "forceitem.h"

namespace qrefuse
{

void RungeKuttaIntegrator::integrate(ForceSimulator *sim, long timestep)
{
	qreal speedLimit = sim->speedLimit();
	qreal vx, vy, v, coeff;
	qreal[][] k, l;

	foreach(ForceItem *item, sim->items())
	{
		coeff = timestep / item->mass;
		k = item->k;
		l = item->l;
		item->prevLocation[0] = item->location[0];
		item->prevLocation[1] = item->location[1];
		k[0][0] = timestep * item->velocity[0];
		k[0][1] = timestep * item->velocity[1];
		l[0][0] = coeff * item->force[0];
		l[0][1] = coeff * item->force[1];

		// Set the position to the new predicted position
		item->location[0] += 0.5f * k[0][0];
		item->location[1] += 0.5f * k[0][1];
	}

	// recalculate forces
	sim->accumulate();

	foreach(ForceItem *item, sim->items())
	{
		coeff = timestep / item->mass;
		k = item->k;
		l = item->l;
		vx = item->velocity[0] + 0.5f * l[0][0];
		vy = item->velocity[1] + 0.5f * l[0][1];
		v = sqrt(vx*vx+vy*vy);
		if (v > speedLimit)
		{
			vx = speedLimit * vx / v;
			vy = speedLimit * vy / v;
		}
		k[1][0] = timestep * vx;
		k[1][1] = timestep * vy;
		l[1][0] = coeff * item->force[0];
		l[1][1] = coeff * item->force[1];

		// Set the position to the new predicted position
		item->location[0] = item->prevLocation[0] + 0.5f * k[1][0];
		item->location[1] = item->prevLocation[1] + 0.5f * k[1][1];
	}

	// recalculate forces
	sim->accumulate();

	foreach(ForceItem *item, sim->items())
	{
		coeff = timestep / item->mass;
		k = item->k;
		l = item->l;
		vx = item->velocity[0] + 0.5f * l[1][0];
		vy = item->velocity[1] + 0.5f * l[1][1];
		v = sqrt(vx*vx+vy*vy);
		if (v > speedLimit)
		{
			vx = speedLimit * vx / v;
			vy = speedLimit * vy / v;
		}
		k[2][0] = timestep * vx;
		k[2][1] = timestep * vy;
		l[2][0] = coeff * item->force[0];
		l[2][1] = coeff * item->force[1];

		// Set the position to the new predicted position
		item->location[0] = item->prevLocation[0] + 0.5f * k[2][0];
		item->location[1] = item->prevLocation[1] + 0.5f * k[2][1];
	}

	// recalculate forces
	sim->accumulate();

	foreach(ForceItem *item, sim->items())
	{
		coeff = timestep / item->mass;
		k = item->k;
		l = item->l;
		QList<qreal> p = item->prevLocation;

		vx = item->velocity[0] + 0.5f * l[2][0];
		vy = item->velocity[1] + 0.5f * l[2][1];
		v = sqrt(vx*vx+vy*vy);
		if (v > speedLimit)
		{
			vx = speedLimit * vx / v;
			vy = speedLimit * vy / v;
		}
		k[3][0] = timestep * vx;
		k[3][1] = timestep * vy;
		l[3][0] = coeff * item->force[0];
		l[3][1] = coeff * item->force[1];

		item->location[0] = p[0] + (k[0][0]+k[3][0])/6.0f + (k[1][0]+k[2][0])/3.0f;
		item->location[1] = p[1] + (k[0][1]+k[3][1])/6.0f + (k[1][1]+k[2][1])/3.0f;

		vx = (l[0][0]+l[3][0])/6.0f + (l[1][0]+l[2][0])/3.0f;
		vy = (l[0][1]+l[3][1])/6.0f + (l[1][1]+l[2][1])/3.0f;
		v = sqrt(vx*vx+vy*vy);
		if (v > speedLimit)
		{
			vx = speedLimit * vx / v;
			vy = speedLimit * vy / v;
		}
		item->velocity[0] += vx;
		item->velocity[1] += vy;
	}
}

}
