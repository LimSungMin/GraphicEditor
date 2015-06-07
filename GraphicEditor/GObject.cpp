#include "stdafx.h"
#include "GObject.h"


GObject::GObject() : m_startX(0), m_startY(0), m_thick(1)
{
}

GObject::GObject(int x, int y) : m_startX(x), m_startY(y), m_thick(1)
{
}

void GObject::setStartX(int x){
	m_startX = x;
}

void GObject::setStartY(int y){
	m_startY = y;
}

int GObject::getStartX(){
	return m_startX;
}

int GObject::getStartY(){
	return m_startY;
}

COLORREF GObject::getLineColor(){
	return m_linecolor;
}

void GObject::setLineColor(COLORREF c){
	m_linecolor = c;
}

void GObject::setLineColor(int r, int g, int b){
	m_linecolor = RGB(r, g, b);
}

COLORREF GObject::getFillColor(){
	return m_panecolor;
}

void GObject::setFillColor(COLORREF c){
	m_panecolor = c;
}

void GObject::setFillColor(int r, int g, int b){
	m_panecolor = RGB(r, g, b);
}


void GObject::setPattern(int pattern){
	m_pattern = pattern;
}

int GObject::getPattern(){
	return m_pattern;
}

int GObject::getThick(){
	return m_thick;
}

void GObject::setThick(int thick){
	m_thick = thick;
}


void GObject::polypointmovecheck(int x)
{
	if (x == 0)
		polypointmove = FALSE;
	else if (x == 1)
		polypointmove = TRUE;
}

void GObject::polyundo(){

}

void GObject::pointmover(int x, int y, int index){

	this->m_polypoints[index].x = x;
	this->m_polypoints[index].y = y;

}

GObject::~GObject()
{
}
