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

	virtual void setPattern(int pattern);
	virtual void setFillPattern(int pattern);
	virtual int getPattern();
	virtual int getFillPattern();
	void setThick(int thick);
	int getThick();

	virtual void setSelected(BOOL selected){ m_isSelected = selected; }
	virtual BOOL isInBound(CPoint point){ return FALSE; }
	virtual int isInSizeBound(CPoint point){ return -1; }
	void setLineColor(COLORREF c);
	void setLineColor(int r, int g, int b);

	void setFillColor(COLORREF c);
	void setFillColor(int r, int g, int b);

	///// poly point만을 위한 함수들 
	void polypointmovecheck(int x);

	void polyundo();
	
	void pointmover(int, int, int);
	CArray<POINT, POINT&> m_polypoints;
	////

	CArray<TCHAR, TCHAR> m_str;
	CArray<TCHAR, TCHAR> m_tmpstr;
	COLORREF getLineColor();
	COLORREF getFillColor();
	int m_groupIndex;

	int m_font;
private:
	int m_startX;
	int m_startY;
	COLORREF m_linecolor;
	int m_thick;
	CPen m_pen;
	int m_pattern;
	int m_fillPattern;
	COLORREF m_panecolor;
	BOOL polypointmove = FALSE;

protected:
	BOOL m_isSelected;
};

