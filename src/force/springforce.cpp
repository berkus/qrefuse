#include <force/springforce.h>
#include <force/forceitem.h>
#include <force/spring.h>
#include <math.h>

namespace qrefuse
{

SpringForce::SpringForce(qreal springCoeff, qreal defaultLength)
{
	params << springCoeff << defaultLength;
	minValues << DEFAULT_MIN_SPRING_COEFF << DEFAULT_MIN_SPRING_LENGTH;
	maxValues << DEFAULT_MAX_SPRING_COEFF << DEFAULT_MAX_SPRING_LENGTH;
	paramsNames << "SpringCoefficient" << "DefaultSpringLength";
}

void SpringForce::updateForceOn(Spring *s)
{
	ForceItem *item1 = s->item1;
	ForceItem *item2 = s->item2;
	qreal length = (s->length < 0 ? params[IDX_SPRING_LENGTH] : s->length);
	qreal x1 = item1->location[0];
	qreal y1 = item1->location[1];
	qreal x2 = item2->location[0];
	qreal y2 = item2->location[1];
	qreal dx = x2-x1;
	qreal dy = y2-y1;
	qreal r  = sqrt(dx*dx+dy*dy);
	if (r == 0.0)
	{
		//range [-0.5..0.5) / 50.0
		dx = ((qreal)random()-(RAND_MAX/2))/RAND_MAX / 50.0f;
		dy = ((qreal)random()-(RAND_MAX/2))/RAND_MAX / 50.0f;
		r  = sqrt(dx*dx+dy*dy);
	}
	qreal d  = r-length;
	qreal coeff = (s->coeff < 0 ? params[IDX_SPRING_COEFF] : s->coeff)*d/r;
	item1->force[0] += coeff * dx;
	item1->force[1] += coeff * dy;
	item2->force[0] += -coeff * dx;
	item2->force[1] += -coeff * dy;
}

}
