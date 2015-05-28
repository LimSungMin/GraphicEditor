#include "stdafx.h"
#include "Point.h"



Point::Point() : x(0), y(0){}
Point::Point(int x1, int y1) : x(x1), y(y1){}


Point::~Point()
{
}

void Point::SetX(int x1){
	x1 = x;
}

void Point::SetY(int y1){
	y1 = y;
}

int Point::GetX(){ return x; }
int Point::GetY(){ return y; }

void Point::SetPoint(int x1, int y1){
	x1 = x;
	y1 = y;
}
