#include "stdafx.h"
#include "GRectangle.h"


GRectangle::GRectangle() : GObject(0, 0), m_endX(0), m_endY(0)
{
	this->setPattern(PS_DOT);
}

GRectangle::GRectangle(int x1, int y1, int x2, int y2) : GObject(x1, y1), m_endX(x2), m_endY(y2)
{
}

void GRectangle::draw(CDC* dc){
	CPen pen(this->getPattern(), this->getThick(), this->getColor());
	dc->SelectObject(&pen);
	dc->SelectStockObject(NULL_BRUSH);
	dc->Rectangle(this->getStartX(), this->getStartY(), this->getEndX(), this->getEndY());
}

int GRectangle::getEndX(){ return m_endX; }
int GRectangle::getEndY(){ return m_endY; }

void GRectangle::setEndX(int x){ m_endX = x; }
void GRectangle::setEndY(int y){ m_endY = y; }

BOOL GRectangle::isInBound(CPoint point){
	if (this->getStartX() <= point.x && point.x <= this->getEndX() || this->getEndX() <= point.x && point.x <= this->getStartX()){
		if (this->getStartY() <= point.y && point.y <= this->getEndY() || this->getEndY() <= point.y && point.y <= this->getStartY()){
			return TRUE;
		}
	}
	return FALSE;
}

void GRectangle::setSelected(BOOL selected){
	if (selected == TRUE){
		MessageBeep(NULL);

	}
	else{

	}
}

void GRectangle::move(int x1, int y1, int x2, int y2){
	this->setStartX(x1);
	this->setStartY(y1);
	this->setEndX(x2);
	this->setEndY(y2);
}

GRectangle::~GRectangle()
{
}
