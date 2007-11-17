#ifndef QREFUSE_NBODYFORCE_H
#define QREFUSE_NBODYFORCE_H

#include <force/force.h>

namespace qrefuse
{

/**
 * Force function which computes an n-body force such as gravity,
 * anti-gravity, or the results of electric charges. This function implements
 * the the Barnes-Hut algorithm for efficient n-body force simulations,
 * using a quad-tree with aggregated mass values to compute the n-body
 * force in O(N log N) time, where N is the number of ForceItems.
 *
 * The algorithm used is that of J. Barnes and P. Hut, in their research
 * paper "A Hierarchical  O(n log n) force calculation algorithm", Nature,
 *  v.324, December 1986. For more details on the algorithm, see one of
 *  the following links --
 * * http://www.cs.berkeley.edu/~demmel/cs267/lecture26/lecture26.html James Demmel's UC Berkeley lecture notes
 * * http://www.physics.gmu.edu/~large/lr_forces/desc/bh/bhdesc.html Description of the Barnes-Hut algorithm
 * * http://www.ifa.hawaii.edu/~barnes/treecode/treeguide.html Joshua Barnes' recent implementation
 *
 * @author http://jheer.org jeffrey heer
 */
class NBodyForce : public Force
{
	public:
		/*
		 * The indexing scheme for quadtree child nodes goes row by row.
		 *   0 | 1    0 -> top left,    1 -> top right
		 *  -------
		 *   2 | 3    2 -> bottom left, 3 -> bottom right
		 */

		static const qreal DEFAULT_GRAV_CONSTANT = -1.0;
		static const qreal DEFAULT_MIN_GRAV_CONSTANT = -10.0;
		static const qreal DEFAULT_MAX_GRAV_CONSTANT = 10.0;

		static const qreal DEFAULT_DISTANCE = -1.0;
		static const qreal DEFAULT_MIN_DISTANCE = -1.0;
		static const qreal DEFAULT_MAX_DISTANCE = 500.0;

		static const qreal DEFAULT_THETA = 0.9;
		static const qreal DEFAULT_MIN_THETA = 0.0;
		static const qreal DEFAULT_MAX_THETA = 1.0;

		enum {
			IDX_GRAVITATIONAL_CONST = 0,
			IDX_MIN_DISTANCE = 1,
			IDX_BARNES_HUT_THETA = 2
		};

		/**
		 * Create a new NBodyForce.
		 * @param gravConstant the gravitational constant to use. Nodes will
		 * attract each other if this value is positive, and will repel each
		 * other if it is negative.
		 * @param minDistance the distance within which two particles will
		 * interact. If -1, the value is treated as infinite.
		 * @param theta the Barnes-Hut parameter theta, which controls when
		 * an aggregated mass is used rather than drilling down to individual
		 * item mass values.
		 */
		NBodyForce(qreal gravConstant = DEFAULT_GRAV_CONSTANT, qreal minDistance = DEFAULT_DISTANCE, qreal theta = DEFAULT_THETA);

		virtual bool isItemForce();

		/**
		 * Clears the quadtree of all entries.
		 */
		void clear();

		void initialize(ForceSimulator *sim);

		/**
		 * Inserts an item into the quadtree.
		 * @param item the ForceItem to add.
		 * @throws IllegalStateException if the current location of the item is
		 *  outside the bounds of the quadtree
		 */
		void insert(ForceItem *item);

		virtual void updateForceOn(ForceItem *item);

	private:
		class QuadTreeNode
		{
			public:
				QuadTreeNode()
				{
					hasChildren = false;
					mass = 0.0;
					com << 0.0 << 0.0;
					value = 0;
					children << 0 << 0 << 0 << 0;
				}

				bool hasChildren;
				qreal mass; // total mass held by this node
				QList<qreal> com; // center of mass of this node
				ForceItem *value; // ForceItem in this node, null if node has children
				QList<QuadTreeNode *> children; // children nodes
		};

		void setBounds(qreal xMin, qreal yMin, qreal xMax, qreal yMax);
		void clearHelper(QuadTreeNode *n);
		static bool isSameLocation(ForceItem *f1, ForceItem *f2);
		void insert(ForceItem *p, QuadTreeNode *n, qreal x1, qreal y1, qreal x2, qreal y2);
		void insertHelper(ForceItem *p, QuadTreeNode *n, qreal x1, qreal y1, qreal x2, qreal y2);
		void calcMass(QuadTreeNode *n);
		void forceHelper(ForceItem *item, QuadTreeNode *n, qreal x1, qreal y1, qreal x2, qreal y2);

		qreal xMin, xMax, yMin, yMax;
		QuadTreeNode *root;
};

}

#endif // QREFUSE_NBODYFORCE_H
