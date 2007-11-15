#include "forceitem.h"
#include <math.h>

namespace qrefuse
{

ForceItem::ForceItem()
{
	mass = 1.0;
	force << 0.0 << 0.0;
	velocity << 0.0 << 0.0;
	location << 0.0 << 0.0;
	prevLocation << 0.0 << 0.0;
	QList init;
	init << 0.0 << 0.0 << 0.0 << 0.0;
	k << init << init;
	l << init << init;
}

ForceItem::ForceItem(const ForceItem &other)
{
	this->mass = other.mass;
	this->force = other.force;
	this->velocity = other.velocity;
	this->location = other.location;
	this->prevLocation = other.prevLocation;
	this->k = other.k;
	this->l = other.l;
}

static bool ForceItem::isValid(ForceItem *item)
{
	return !(isnan(item->location[0]) || isnan(item->location[1]) ||
			 isnan(item->prevLocation[0]) || isnan(item->prevLocation[1]) ||
			 isnan(item->velocity[0]) || isnan(item->velocity[1]) ||
			 isnan(item->force[0]) || isnan(item->force[1]));
}

}
