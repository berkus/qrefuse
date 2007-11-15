/**
 * A viscosity/drag force to help stabilize items.
 */
class DragForce : public AbstractForce
{
	public:
		static const qreal DEFAULT_DRAG_COEFF = 0.01f;
		static const qreal DEFAULT_MIN_DRAG_COEFF = 0.0f;
		static const qreal DEFAULT_MAX_DRAG_COEFF = 0.1f;

		static const qreal IDX_DRAG_COEFF = 0;

		DragForce(qreal dragCoeff = DEFAULT_DRAG_COEFF);

		virtual bool isItemForce() { return true; }

		virtual QStringList parameterNames();
		virtual void updateForcesOn(ForceItem &item);
};
