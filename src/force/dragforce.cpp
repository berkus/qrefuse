#include <force/dragforce.h>
#include <force/forceitem.h>

namespace qrefuse
{

const qreal DragForce::DEFAULT_DRAG_COEFF/* = 0.01f*/;
const qreal DragForce::DEFAULT_MIN_DRAG_COEFF/* = 0.0f*/;
const qreal DragForce::DEFAULT_MAX_DRAG_COEFF/* = 0.1f*/;

DragForce::DragForce(qreal dragCoeff)
{
	params << dragCoeff;
	minValues << DEFAULT_MIN_DRAG_COEFF;
	maxValues << DEFAULT_MAX_DRAG_COEFF;
	paramsNames << "DragCoefficient";
}

void DragForce::updateForceOn(ForceItem *item)
{
	item->force[0] -= params[IDX_DRAG_COEFF] * item->velocity[0];
	item->force[1] -= params[IDX_DRAG_COEFF] * item->velocity[1];
}

bool DragForce::isItemForce() { return true; }

}
