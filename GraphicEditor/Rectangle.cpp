#include "stdafx.h"
#include "Rectangle.h"


JRectangle::JRectangle()
{
}

JRectangle::JRectangle(Line l){
	
}

JRectangle::JRectangle(POINT p1, POINT p2){
	SetStart(p1.x, p1.y);
	SetEnd(p2.x, p2.y);
}

void JRectangle::SetSize(int x1, int y1, int x2, int y2){
	SetStart(x1, y1);
	SetEnd(x2, y2);
}

JRectangle::~JRectangle()
{
}
