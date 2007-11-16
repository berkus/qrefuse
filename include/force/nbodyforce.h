#ifndef QREFUSE_NBODYFORCE_H
#define QREFUSE_NBODYFORCE_H

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
    /*
     * The indexing scheme for quadtree child nodes goes row by row.
     *   0 | 1    0 -> top left,    1 -> top right
     *  -------
     *   2 | 3    2 -> bottom left, 3 -> bottom right
     */
};

}

#endif // QREFUSE_NBODYFORCE_H
