#ifndef QREFUSE_RUNGEKUTTAINTEGRATOR_H
#define QREFUSE_RUNGEKUTTAINTEGRATOR_H

#include "integrator.h"

namespace qrefuse
{

class RungeKuttaIntegrator : public Integrator
{
	public:
    	virtual void integrate(ForceSimulator *sim, long timestep);
};

}

#endif // QREFUSE_RUNGEKUTTAINTEGRATOR_H
