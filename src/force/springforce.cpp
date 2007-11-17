#include <force/springforce.h>
#include <force/forceitem.h>
#include <force/spring.h>
#include <math.h>
#include <QtDebug>

namespace qrefuse
{

const qreal SpringForce::DEFAULT_SPRING_COEFF/* = 1E-4f*/;
const qreal SpringForce::DEFAULT_MAX_SPRING_COEFF/* = 1E-3f*/;
const qreal SpringForce::DEFAULT_MIN_SPRING_COEFF/* = 1E-5f*/;
const qreal SpringForce::DEFAULT_SPRING_LENGTH/* = 50*/;
const qreal SpringForce::DEFAULT_MIN_SPRING_LENGTH/* = 0*/;
const qreal SpringForce::DEFAULT_MAX_SPRING_LENGTH/* = 200*/;

SpringForce::SpringForce(qreal springCoeff, qreal defaultLength)
{
	params << springCoeff << defaultLength;
	minValues << DEFAULT_MIN_SPRING_COEFF << DEFAULT_MIN_SPRING_LENGTH;
	maxValues << DEFAULT_MAX_SPRING_COEFF << DEFAULT_MAX_SPRING_LENGTH;
	paramsNames << "SpringCoefficient" << "DefaultSpringLength";
}

bool SpringForce::isSpringForce() { return true; }

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
// 	qDebug("Spring updating item forces: coeff %f, dx %f, dy %f", coeff, dx, dy);
// 	qDebug("before %f,%f / %f,%f", item1->force[0], item1->force[1], item2->force[0], item2->force[1]);
	item1->force[0] += coeff * dx;
	item1->force[1] += coeff * dy;
	item2->force[0] += -coeff * dx;
	item2->force[1] += -coeff * dy;
// 	qDebug("after  %f,%f / %f,%f", item1->force[0], item1->force[1], item2->force[0], item2->force[1]);
}

}
