#ifndef QREFUSE_INTEGRATOR_H
#define QREFUSE_INTEGRATOR_H

namespace qrefuse
{

class ForceSimulator;

class Integrator
{
	public:
    	virtual void integrate(ForceSimulator *sim, long timestep) = 0;
};

}

#endif // QREFUSE_INTEGRATOR_H
