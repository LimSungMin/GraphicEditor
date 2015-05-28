#pragma once
#include "Object.h"
#include "Point.h"
class Line :
	public Point
{
public:
	Line();
	~Line();
private:
	int endx, endy;
	BOOL toggle;
};

