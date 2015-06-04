#pragma once
#include "GObject.h"
class GRectangle :
	public GObject
{
public:
	GRectangle();
	GRectangle(int x1, int y1, int x2, int y2);
	virtual ~GRectangle();
	virtual void draw(CDC* dc);
	void setEndX(int x);
	void setEndY(int y);
	int getEndX();
	int getEndY();
	void move(int x1, int y1, int x2, int y2);
private:
	int m_endX;
	int m_endY;
	int m_mode;
};