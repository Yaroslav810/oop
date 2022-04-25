#include "../../../Point/CPoint.h"
#include "../CSolidShape.h"

class CCircle : public CSolidShape
{
public:
	CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor);

private:
	CPoint m_center;
	double m_radius;
};
