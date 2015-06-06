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
	
	void setPattern(int pattern);
	int getPattern();
	void setThick(int thick);
	int getThick();
	
	void setLineColor(COLORREF c);
	void setLineColor(int r, int g, int b);

	void setFillColor(COLORREF c);
	void setFillColor(int r, int g, int b);
	
	
	COLORREF getLineColor();
	COLORREF getFillColor();



private:
	int m_startX;
	int m_startY;
	COLORREF m_linecolor;
	COLORREF m_panecolor;
	int m_thick;
	CPen m_pen;
	int m_pattern;
};

