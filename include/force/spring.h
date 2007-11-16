#ifndef QREFUSE_SPRING_H
#define QREFUSE_SPRING_H

namespace qrefuse
{

class ForceItem;

/**
 * Represents a spring in a force simulation.
 */
class Spring
{
	public:
		/**
		 * Create a new Spring instance
		 * @param fi1 the first ForceItem endpoint
		 * @param fi2 the second ForceItem endpoint
		 * @param k the spring tension co-efficient
		 * @param len the spring's resting length
		 */
		Spring(ForceItem *fi1, ForceItem *fi2, qreal k, qreal len)
		{
			item1 = fi1;
			item2 = fi2;
			coeff = k;
			length = len;
		}

		/** The first ForceItem endpoint */
		ForceItem *item1;
		/** The second ForceItem endpoint */
		ForceItem *item2;
		/** The spring's resting length */
		qreal length;
		/** The spring tension co-efficient */
		qreal coeff;
};

}

#endif
