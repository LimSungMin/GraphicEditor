#include "stdafx.h"
#include "GRectangle.h"


GRectangle::GRectangle() : GObject(0, 0), m_endX(0), m_endY(0)
{
}

void GRectangle::draw(CDC* dc, int mode){
	CPen pen(this->getPattern(), this->getThick(), this->getColor());
	dc->SelectObject(&pen);
	dc->Rectangle(this->getStartX(), this->getStartY(), this->getEndX(), this->getEndY());
}

int GRectangle::getEndX(){ return m_endX; }
int GRectangle::getEndY(){ return m_endY; }

void GRectangle::setEndX(int x){ m_endX = x; }
void GRectangle::setEndY(int y){ m_endY = y; }

GRectangle::~GRectangle()
{
}
