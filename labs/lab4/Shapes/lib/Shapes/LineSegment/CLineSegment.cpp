#include "CLineSegment.h"

CLineSegment::CLineSegment(CPoint x, CPoint y, uint32_t color)
	: m_startPoint(x)
	, m_endPoint(y)
	, CShape(color)
{
}
