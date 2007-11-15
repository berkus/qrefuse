class ForceItem
{
	// Do java people know OOP?
	public:
		/** The mass value of this ForceItem. */
		qreal mass;
		/** The values of the forces acting on this ForceItem. */
		QList<qreal> force;
		/** The velocity values of this ForceItem. */
		QList<qreal> velocity;
		/** The location values of this ForceItem. */
		QList<qreal> location;
		/** The previous location values of this ForceItem. */
		QList<qreal> prevLocation;
		/** Temporary variables for Runge-Kutta integration */
		QList< QList<qreal> > k;
		/** Temporary variables for Runge-Kutta integration */
		QList< QList<qreal> > l;
};
