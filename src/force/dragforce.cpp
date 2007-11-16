#include <force/dragforce.h>
#include <force/forceitem.h>

namespace qrefuse
{

DragForce::DragForce(qreal dragCoeff)
{
	params << dragCoeff;
	minValues << DEFAULT_MIN_DRAG_COEFF;
	maxValues << DEFAULT_MAX_DRAG_COEFF;
	paramsNames << "DragCoefficient";
}

void DragForce::updateForcesOn(ForceItem *item)
{
	item->force[0] -= params[IDX_DRAG_COEFF] * item->velocity[0];
	item->force[1] -= params[IDX_DRAG_COEFF] * item->velocity[1];
}

}
