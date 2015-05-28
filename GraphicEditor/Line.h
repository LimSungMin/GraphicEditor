#pragma once
class Line	
{
public:
	Line();
	~Line();
	void SetEnd(int x, int y);
	void SetStart(int x, int y);
	int getX();
	int getY();
	POINT getxy();
private:
	int startx, starty;
	int endx, endy;

	
};

