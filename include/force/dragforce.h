#ifndef QREFUSE_DRAGFORCE_H
#define QREFUSE_DRAGFORCE_H

#include <force/force.h>

namespace qrefuse
{

class ForceItem;

/**
 * Implements a viscosity/drag force to help stabilize items.
 *
 * @author <a href="http://jheer.org">jeffrey heer</a>
 */
class DragForce : public Force
{
	public:
		static const qreal DEFAULT_DRAG_COEFF = 0.01f;
		static const qreal DEFAULT_MIN_DRAG_COEFF = 0.0f;
		static const qreal DEFAULT_MAX_DRAG_COEFF = 0.1f;

		enum {
			IDX_DRAG_COEFF = 0
		};

		DragForce(qreal dragCoeff = DEFAULT_DRAG_COEFF);
		virtual bool isItemForce();
		virtual void updateForceOn(ForceItem *item);
};

}

#endif // QREFUSE_DRAGFORCE_H
