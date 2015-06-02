#include "stdafx.h"
#include "GRectangle.h"


GRectangle::GRectangle()
{
}

void GRectangle::draw(CDC* dc, int mode){
	dc->Rectangle(this->getStartX(), this->getStartY(), this->getEndX(), this->getEndY());
}

int GRectangle::getEndX(){ return m_endX; }
int GRectangle::getEndY(){ return m_endY; }

void GRectangle::setEndX(int x){ m_endX = x; }
void GRectangle::setEndY(int y){ m_endY = y; }

GRectangle::~GRectangle()
{
}
