#pragma once
#include "GObject.h"
class GEllipse :
	public GObject
{
public:
	GEllipse();
	~GEllipse();
	void SetEnd(POINT point);
	POINT GetEnd();

	void draw(CDC* dc);
	/*
	void move(int x1, int y1, int x2, int y2);
	BOOL isInBound(CPoint point);
	void setSelected(BOOL selected);
	int isInSizeBound(CPoint point);
	*/
private:
	int m_endX;
	int m_endY;
	//CRect* m_selectedRect[4];
};

