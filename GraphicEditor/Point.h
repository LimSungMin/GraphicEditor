#pragma once
class Point
{
public:
	Point();
	Point(int x1, int y2);
	void SetX(int x1);
	void SetY(int y1);
	int GetX();
	int GetY();
	void SetPoint(int x1, int y2);
	~Point();
private:
	int x;
	int y;
};
