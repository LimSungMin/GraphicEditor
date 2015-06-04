#include "stdafx.h"
#include "GLine.h"


GLine::Line()	
	:startx(0), starty(0), endx(0), endy(0)
{
	
}


GLine::~Line()
{
}

void GLine::SetStart(int x, int y){
	startx = x;
	starty = y;
}
void GLine::SetEnd(int x, int y){
	endx = x;
	endy = y;
}

int GLine::getX()
{
	return startx;
}
int GLine::getY()
{
	return starty;
}

POINT GLine::getstart(){
	POINT pos;
	pos.x = startx;
	pos.y = starty;
	return pos;
}
POINT GLine::getend(){
	POINT pos;
	pos.x = endx;
	pos.y = endy;
	return pos;
}