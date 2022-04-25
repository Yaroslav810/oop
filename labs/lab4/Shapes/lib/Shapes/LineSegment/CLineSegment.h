#include "../../Point/CPoint.h"
#include "../CShape.h"

class CLineSegment : public CShape
{
public:
	CLineSegment(CPoint x, CPoint y, uint32_t color);

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
};
