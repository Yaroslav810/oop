#pragma once
#include <string>

class CPoint
{
public:
	CPoint(double x, double y);
	[[nodiscard]] double GetX() const;
	[[nodiscard]] double GetY() const;
	bool operator==(const CPoint& point) const;
	[[nodiscard]] std::string ToString() const;

private:
	double m_x;
	double m_y;
};
