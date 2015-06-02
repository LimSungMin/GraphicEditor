#pragma once
class GObject
{
public:
	GObject();
	GObject(int x, int y);
	virtual ~GObject();
	virtual void draw(CDC* dc, int x, int y); // 다른 곳에서도 draw가 있으니까.
	void setStartX(int x);
	void setStartY(int y);
	int getStartX();
	int getStartY();
	void setColor(COLORREF c);
	void setColor(int r, int g, int b);
	void setPattern(int pattern);
	int getPattern();
	void setThick(double thick);
	double getThick();
	COLORREF getColor();
private:
	int m_startX;
	int m_startY;
	COLORREF m_color;
	double m_thick;
	CPen m_pen;
	int m_pattern;
};

