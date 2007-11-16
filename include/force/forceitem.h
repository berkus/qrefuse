#ifndef QREFUSE_FORCEITEM_H
#define QREFUSE_FORCEITEM_H

#include <QList>

namespace qrefuse
{

/**
 * Represents a point particle in a force simulation, maintaining values for
 * mass, forces, velocity, and position.
 */
class ForceItem
{
	public:
		ForceItem();
		ForceItem(const ForceItem &other);

		/**
		 * Checks a ForceItem to make sure its values are all valid numbers
		 * (i.e., not NaNs).
		 * @param item the item to check
		 * @return true if all the values are valid, false otherwise
		 */
		static bool isValid(ForceItem *item);

		/** The mass value of this ForceItem. */
		qreal mass;
		/** The values of the forces acting on this ForceItem. */
		QList<qreal> force;
		/** The velocity values of this ForceItem. */
		QList<qreal> velocity;
		/** The location values of this ForceItem. */
		QList<qreal> location;
		/** The previous location values of this ForceItem. */
		QList<qreal> prevLocation;
		/** Temporary variables for Runge-Kutta integration */
		QList< QList<qreal> > k;
		/** Temporary variables for Runge-Kutta integration */
		QList< QList<qreal> > l;
};

}

#endif // QREFUSE_FORCEITEM_H
