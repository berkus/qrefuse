#include <force/forcesimulator.h>
#include <force/rungekuttaintegrator.h>
#include <force/force.h>
#include <force/spring.h>
#include <force/forceitem.h>

#include <QtDebug>

namespace qrefuse
{

ForceSimulator::ForceSimulator(Integrator *intgr)
	: m_speedLimit(1.0f)
	, m_integrator(intgr)
{
	if (!intgr)
		m_integrator = new RungeKuttaIntegrator;
}

void ForceSimulator::setSpeedLimit(qreal limit)
{
	m_speedLimit = limit;
}

qreal ForceSimulator::speedLimit()
{
	return m_speedLimit;
}

void ForceSimulator::setIntegrator(Integrator *intgr)
{
	m_integrator = intgr;
}

Integrator *ForceSimulator::integrator()
{
	return m_integrator;
}

void ForceSimulator::addForce(Force *f)
{
	if (f->isItemForce())
	{
		qDebug("Adding item force %p", f);
		itemForces.append(f);
	}

	if (f->isSpringForce())
	{
		qDebug("Adding spring force %p", f);
		springForces.append(f);
	}
}

ForceSimulator::ForceList ForceSimulator::forces()
{
	return itemForces + springForces;
}

void ForceSimulator::addItem(ForceItem *i)
{
	m_items.append(i);
}

bool ForceSimulator::removeItem(ForceItem *i)
{
	return m_items.removeAll(i) > 0;
}

ForceSimulator::ItemList ForceSimulator::items()
{
	return m_items;
}

Spring *ForceSimulator::addSpring(ForceItem *item1, ForceItem *item2, float coeff, float length)
{
	if (!item1 || !item2)
		return 0;
	Spring *s = new Spring(item1, item2, coeff, length);
	m_springs.append(s);
	return s;
}

ForceSimulator::SpringList ForceSimulator::springs()
{
	return m_springs;
}

void ForceSimulator::run(long timestep)
{
	accumulate();
	m_integrator->integrate(this, timestep);
}

void ForceSimulator::accumulate()
{
	foreach(Force *force, itemForces)
		force->initialize(this);

	foreach(Force *force, springForces)
		force->initialize(this);

	foreach(ForceItem *item, m_items)
	{
		item->force[0] = 0.0;
		item->force[1] = 0.0;
		foreach(Force *force, itemForces)
			force->updateForceOn(item);
	}

	foreach(Spring *spring, m_springs)
		foreach(Force *force, springForces)
			force->updateForceOn(spring);
}

}
