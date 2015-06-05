#include "stdafx.h"
#include "GPolyline.h"


GPolyline::GPolyline() : GObject(0, 0), m_endX(0), m_endY(0)
{
}

void GPolyline::draw(CDC* dc){

	dc->Polyline(this->m_polypoints.GetData(), this->m_polypoints.GetCount());
}

void GPolyline::polypointset(POINT point){ m_polypoints.Add(point); }

int GPolyline::getEndX(){ return m_endX; }
int GPolyline::getEndY(){ return m_endY; }

void GPolyline::setEndX(int x){ m_endX = x; }
void GPolyline::setEndY(int y){ m_endY = y; }

GPolyline::~GPolyline()
{
}
