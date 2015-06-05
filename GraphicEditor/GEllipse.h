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
private:
	int m_endX;
	int m_endY;
};

