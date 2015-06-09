#pragma once
#include "GObject.h"

// GTextBox

class GTextBox : public GObject
{
	

public:
	GTextBox();
	virtual ~GTextBox();

	virtual void draw(CDC* dc);
	void setEndX(int x);
	void setEndY(int y);
	int getEndX();
	int getEndY();
	void move(int x1, int y1, int x2, int y2);
	BOOL isInBound(CPoint point);
	void setSelected(BOOL selected);
	int isInSizeBound(CPoint point);
	int m_fontsize;
	void setEndXY(int, int);

private:
	int m_textendX;
	int m_textendY;
	int m_mode;
	CRect* m_selectedRect[4];
	
protected:
	
};


