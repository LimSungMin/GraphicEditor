#pragma once
#include "GObject.h"
class GLine	: public GObject
{
public:
	GLine();
	~GLine();
	void SetEnd(POINT point);
	POINT GetEnd();

	// 다른 애들 거
	void draw(CDC* dc);
	
	
	void move(int x1, int y1, int x2, int y2);
	BOOL isInBound(CPoint point);
	void setSelected(BOOL selected);
	int isInSizeBound(CPoint point);
	
private:
	int m_endX;
	int m_endY;
	int m_mode;	
	CRect* m_selectedRect[2];
};

