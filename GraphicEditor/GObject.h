#pragma once
class GObject
{
public:
	GObject();
	GObject(int x, int y);
	GObject(const GObject& objectSrc){ *this = objectSrc; }
	GObject& operator=(const GObject& objectSrc) { return *this; }
	virtual ~GObject();
	virtual void draw(CDC* dc){} // 다른 곳에서도 draw가 있으니까.
	void setStartX(int x);
	void setStartY(int y);
	int getStartX();
	int getStartY();
	virtual void setEndX(int x){}
	virtual void setEndY(int y){}
	virtual int getEndX(){ return 0; }
	virtual int getEndY(){ return 0; }
	virtual void move(int x1, int y1, int x2, int y2){}
	virtual BOOL getSelected(){ return m_isSelected; }
	void setColor(COLORREF c);
	void setColor(int r, int g, int b);
	virtual void setPattern(int pattern);
	virtual int getPattern();
	void setThick(int thick);
	int getThick();
	COLORREF getColor();
	virtual void setSelected(BOOL selected){ m_isSelected = selected; }
	virtual BOOL isInBound(CPoint point){ return FALSE; }
private:
	int m_startX;
	int m_startY;
	COLORREF m_color;
	int m_thick;
	CPen m_pen;
	int m_pattern;
	COLORREF m_colorFill;
protected:
	BOOL m_isSelected;
};

