#include "stdafx.h"
#include "Line.h"


Line::Line()	
	:startx(0), starty(0), endx(0), endy(0)
{
	
}


Line::~Line()
{
}

void Line::SetStart(int x, int y){
	startx = x;
	starty = y;
}
void Line::SetEnd(int x, int y){
	endx = x;
	endy = y;
}

int Line::getX()
{
	return startx;
}
int Line::getY()
{
	return starty;
}

POINT Line::getstart(){
	POINT pos;
	pos.x = startx;
	pos.y = starty;
	return pos;
}
POINT Line::getend(){
	POINT pos;
	pos.x = endx;
	pos.y = endy;
	return pos;
}