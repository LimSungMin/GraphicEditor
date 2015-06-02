#include "stdafx.h"
#include "GObject.h"


GObject::GObject() : m_startX(0), m_startY(0)
{
}

GObject::GObject(int x, int y) : m_startX(x), m_startY(y)
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

COLORREF GObject::getColor(){
	return m_color;
}

void GObject::setColor(COLORREF c){
	m_color = c;
}

void GObject::setColor(int r, int g, int b){
	m_color = RGB(r, g, b);
}

void GObject::setPattern(int pattern){
	m_pattern = pattern;
}

int GObject::getPattern(){
	return m_pattern;
}

double GObject::getThick(){
	return m_thick;
}

void GObject::setThick(double thick){
	m_thick = thick;
}

void GObject::draw(CDC* dc, int x, int y){
	CPen pen(this->getPattern(), this->getThick(), this->getColor());
	dc->Rectangle(this->getStartX(), this->getStartY(), x, y);
}

GObject::~GObject()
{
}
