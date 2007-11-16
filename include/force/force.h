#ifndef QREFUSE_FORCE_H
#define QREFUSE_FORCE_H

#include <QList>
#include <QStringList>

namespace qrefuse
{

class Spring;
class ForceItem;
class ForceSimulator;

class Force
{
	public:
		void initialize(ForceSimulator *sim);

		int parametersCount() { return params.size(); }
		qreal parameterAt(int i);
		qreal minValueAt(int i);
		qreal maxValueAt(int i);
		QString parameterNameAt(int i);
		virtual QStringList parameterNames() = 0;
		void setParameterAt(int i, qreal value);
		void setMinValueAt(int i, qreal value);
		void setMaxValueAt(int i, qreal value);

		virtual bool isItemForce() { return false; }
		virtual bool isSpringForce() { return false; }

		virtual void updateForceOn(ForceItem *item);
		virtual void updateForceOn(Spring *spring);

	protected:
		QList<qreal> params;
		QList<qreal> minValues;
		QList<qreal> maxValues;
};

}

#endif
