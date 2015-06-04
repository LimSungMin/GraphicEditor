#pragma once
#include "GObject.h"
class GPolyline :
	public GObject
{
public:
	GPolyline();
	virtual ~GPolyline();
	virtual void draw(CDC* dc);
	void setEndX(int x);
	void setEndY(int y);
	int getEndX();
	int getEndY();
	void move(int x1, int y1, int x2, int y2);
	
	void polypointset(POINT point);


private:
	int m_endX;
	int m_endY;
	int m_mode; 
	CArray<POINT, POINT&> m_polypoints;
};