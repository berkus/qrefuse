#ifndef QREFUSE_FORCESIMULATOR_H
#define QREFUSE_FORCESIMULATOR_H

#include <QList>

namespace qrefuse
{

class Integrator;
class ForceItem;
class Spring;

/**
 * Manages a simulation of physical forces acting on bodies. To create a
 * custom ForceSimulator, add the desired @link Force functions and choose an
 * appropriate @link Integrator.
 */
class ForceSimulator
{
	public:
		ForceSimulator(Integrator *intgr = 0);

		void setSpeedLimit(qreal limit);
		qreal speedLimit();

		void setIntegrator(Integrator *intgr);
		Integrator *integrator();

		/**
		 * Clear this simulator, removing all ForceItem and Spring instances
		 * for the simulator.
		 */
		void clear();

		void addForce(Force *f);

		/**
		 * Get an array of all the Force functions used in this simulator.
		 * @return an array of Force functions
		 */
		typedef QList<Force *> ForceList;
		ForceList forces();

		void addItem(ForceItem *i);
		bool removeItem(ForceItem *i);

		typedef QList<ForceItem *> ItemList;
		ItemList::iterator items();

    	Spring *addSpring(ForceItem *item1, ForceItem *item2, float coeff = -1.0, float length = -1.0);

		typedef QList<Spring *> SpringList;
		SpringList::iterator springs();

		/**
		 * Run the simulator for one timestep.
		 * @param timestep the span of the timestep for which to run the simulator
		 */
		void run(long timestep);

		/**
		 * Accumulate all forces acting on the items in this simulation.
		 */
		void accumulate();

	private:
		ItemList m_items;
		SpringList m_springs;
		ForceList itemForces;
		ForceList springForces;
		Integrator *m_integrator;
		qreal m_speedLimit;
};

}

#endif // QREFUSE_FORCESIMULATOR_H
