#ifndef QREFUSE_SPRINGFORCE_H
#define QREFUSE_SPRINGFORCE_H

#include <force/force.h>

namespace qrefuse
{

/**
 * Force function that computes the force acting on ForceItems due to a
 * given Spring.
 *
 * @author <a href="http://jheer.org">jeffrey heer</a>
 */
class SpringForce : public Force
{
	public:
		static const qreal DEFAULT_SPRING_COEFF = 1E-4f;
		static const qreal DEFAULT_MAX_SPRING_COEFF = 1E-3f;
		static const qreal DEFAULT_MIN_SPRING_COEFF = 1E-5f;
		static const qreal DEFAULT_SPRING_LENGTH = 50;
		static const qreal DEFAULT_MIN_SPRING_LENGTH = 0;
		static const qreal DEFAULT_MAX_SPRING_LENGTH = 200;

		static const int IDX_SPRING_COEFF = 0;
		static const int IDX_SPRING_LENGTH = 1;

		/**
		 * Create a new SpringForce.
		 * @param springCoeff the default spring co-efficient to use. This will
		 * be used if the spring's own co-efficient is less than zero.
		 * @param defaultLength the default spring length to use. This will
		 * be used if the spring's own length is less than zero.
		 */
		SpringForce(qreal springCoeff = DEFAULT_SPRING_COEFF, qreal defaultLength = DEFAULT_SPRING_LENGTH);
		virtual bool isSpringForce() { return true; }
		virtual void updateForceOn(Spring *spring);
};

}

#endif // QREFUSE_SPRINGFORCE_H
