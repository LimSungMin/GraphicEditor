#pragma once
class GLine	: CObject
{
public:
	GLine();
	~GLine();
	void SetEnd(int x, int y);
	void SetStart(int x, int y);
	int getX();
	int getY();
	POINT getstart();
	POINT getend();
private:
	int startx, starty;
	int endx, endy;

	
};

