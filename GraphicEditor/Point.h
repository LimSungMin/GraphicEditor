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

Point::Point() : x(0), y(0){}
Point::Point(int x1, int y1) : x(x1), y(y1){}

void Point::SetX(int x1){
	x1 = x;
}

void Point::SetY(int y1){
	y1 = y;
}

int Point::GetX(){ return x; }
int Point::GetY(){ return y; }

void Point::SetPoint(int x1, int y1){
	x1 = x;
	y1 = y;
}
