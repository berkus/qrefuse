#include <force/force.h>

namespace qrefuse
{

void Force::initialize(ForceSimulator *sim)
{
	/* Do nothing */
}

QStringList Force::parameterNames()
{
	return paramsNames;
}

qreal Force::parameterAt(int i)
{
	Q_ASSERT( i >= 0 );
	Q_ASSERT( i < params.size() );
	return params[i];
}

qreal Force::minValueAt(int i)
{
	Q_ASSERT( i >= 0 );
	Q_ASSERT( i < minValues.size() );
	return minValues[i];
}

qreal Force::maxValueAt(int i)
{
	Q_ASSERT( i >= 0 );
	Q_ASSERT( i < maxValues.size() );
	return maxValues[i];
}

QString Force::parameterNameAt(int i)
{
	QStringList list = parameterNames();
	Q_ASSERT( i >= 0 );
	Q_ASSERT( i < list.size() );
	return list[i];
}

void Force::setParameterAt(int i, qreal value)
{
	Q_ASSERT( i >= 0 );
	Q_ASSERT( i < params.size() );
	params[i] = value;
}

void Force::setMinValueAt(int i, qreal value)
{
	Q_ASSERT( i >= 0 );
	Q_ASSERT( i < minValues.size() );
	minValues[i] = value;
}

void Force::setMaxValueAt(int i, qreal value)
{
	Q_ASSERT( i >= 0 );
	Q_ASSERT( i < maxValues.size() );
	maxValues[i] = value;
}

void Force::updateForceOn(ForceItem *item)
{
	qFatal(__PRETTY_FUNCTION__);
}

void Force::updateForceOn(Spring *spring)
{
	qFatal(__PRETTY_FUNCTION__);//" is not supported.");
}

}
