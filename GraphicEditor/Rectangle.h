#pragma once
#include "Line.h"


class JRectangle : public Line
{
public:
	JRectangle();
	JRectangle(POINT p1, POINT p2);
	JRectangle(Line l);
	void SetSize(int x1, int y1, int x2, int y2);
	virtual ~JRectangle();
	void SetBackground(COLORREF rgb);

private:
	
};

