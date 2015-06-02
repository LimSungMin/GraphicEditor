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

GRectangle::~GRectangle()
{
}
