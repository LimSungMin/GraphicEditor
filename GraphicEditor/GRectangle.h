#pragma once
#include "GObject.h"
class GRectangle :
	public GObject
{
public:
	GRectangle();
	virtual ~GRectangle();
	virtual void draw(CDC* dc, int x, int y, int mode);
private:
	int m_endX;
	int m_endY;
	int m_mode;
};

