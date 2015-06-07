#include "stdafx.h"
#include "GPolyline.h"


GPolyline::GPolyline() : GObject(0, 0), m_endX(0), m_endY(0)
{
}

void GPolyline::draw(CDC* dc){

	CPen pen(this->getPattern(),this->getThick(), this->getLineColor());
	dc->SelectObject(&pen);
	dc->Polyline(this->m_polypoints.GetData(), this->m_polypoints.GetCount());

	if (this->getSelected() == TRUE){
		//MessageBeep(1);
		
		CBrush brush(RGB(255, 255, 255));
		dc->SelectObject(&brush);
		m_selectedRect[0] = new CRect(this->findleftest() - 5, this->findhighest() - 5, this->findleftest() + 5, this->findhighest() + 5);
		dc->Rectangle(m_selectedRect[0]);

		CBrush brush1(RGB(255, 0, 0));
		dc->SelectObject(&brush1);
		m_selectedRect[1] = new CRect(this->findrightest() - 5, this->findhighest() - 5, this->findrightest() + 5, this->findhighest() + 5);
		dc->Rectangle(m_selectedRect[1]);

		CBrush brush2(RGB(0, 255, 0));
		dc->SelectObject(&brush2);
		m_selectedRect[2] = new CRect(this->findleftest() - 5, this->findlowest() - 5, this->findleftest() + 5, this->findlowest() + 5);
		dc->Rectangle(m_selectedRect[2]);

		CBrush brush3(RGB(0, 0, 255));
		dc->SelectObject(&brush3);
		m_selectedRect[3] = new CRect(this->findrightest() - 5, this->findlowest() - 5, this->findrightest() + 5, this->findlowest() + 5); // 메모리 누수의 위험 있음. 수정바람!
		dc->Rectangle(m_selectedRect[3]);
		
		
		
		CPen pen2(PS_DASH, this->getThick(), this->getLineColor());
		dc->SelectStockObject(NULL_BRUSH);
		dc->SelectObject(&pen2);
		m_selectedRect[4] = new CRect(this->findleftest(), this->findhighest(), this->findrightest(), this->findlowest());
		dc->Rectangle(m_selectedRect[4]);

		for (int i = 0; i < this->m_polypoints.GetCount(); i++)
		{
			dc->SelectObject(&brush);
			m_selectedPointRect[i] = new CRect(this->m_polypoints[i].x - 5, this->m_polypoints[i].y - 5, this->m_polypoints[i].x + 5, this->m_polypoints[i].y + 5);
			dc->Rectangle(m_selectedPointRect[i]);
		}
		
	}
}

// statrtx = right / starty = high / endx = left / endy = low


void GPolyline::polypointset(POINT point){ m_polypoints.Add(point); }

int GPolyline::getEndX(){ return m_endX; }
int GPolyline::getEndY(){ return m_endY; }

void GPolyline::setEndX(int x){ m_endX = x; }
void GPolyline::setEndY(int y){ m_endY = y; }

void GPolyline::move(int x1, int y1, int x2, int y2){
	// 각 좌표 이동값의 차를 인수로 받으므로, 해당 값 만큼을 기존 위치에 더함

	if (this->polypointmove == FALSE)
		this->totalmover(x1, y1);

	else if (this->polypointmove == TRUE)
		this->pointmover(x1, y1, x2);
}

void GPolyline::totalmover(int x, int y)
{
	for (int i = 0; i < this->m_polypoints.GetCount(); i++)
		m_polypoints[i].x += x;

	for (int i = 0; i < this->m_polypoints.GetCount(); i++)
		m_polypoints[i].y += y;

}


int GPolyline::findhighest()
{
	POINT tmppoint;

	int highest = 9999;

	for (int i = 0; i < this->m_polypoints.GetCount(); i++)
	{
		tmppoint = m_polypoints[i];
	
		if (tmppoint.y < highest)
			highest = tmppoint.y;
	}

	return highest;
}

int GPolyline::isInSizeBound(CPoint point){
	for (int i = 0; i < this->m_polypoints.GetCount() ; i++){
		if (this->m_selectedPointRect[i]->left <= point.x && point.x <= this->m_selectedPointRect[i]->right
			|| this->m_selectedPointRect[i]->right <= point.x && point.x <= this->m_selectedPointRect[i]->left){
			
			if (this->m_selectedPointRect[i]->top <= point.y && point.y <= this->m_selectedPointRect[i]->bottom ||
				this->m_selectedPointRect[i]->bottom <= point.y && point.y <= this->m_selectedPointRect[i]->top){
				//MessageBox(1);
				return i;
			}
		}
	}

	return -1;
}

void GPolyline::pointmover(int x, int y, int index){
	
	this->m_polypoints[index].x += x;
	this->m_polypoints[index].y += y;
}

void GPolyline::polypointmovecheck(int x)
{
	if (x == 0)
		polypointmove = FALSE;
	else if (x == 1)
		polypointmove = TRUE;
}

int GPolyline::findlowest()
{
	POINT tmppoint;

	int lowest = 0;

	for (int i = 0; i < this->m_polypoints.GetCount(); i++)
	{
		tmppoint = m_polypoints[i];

		if (tmppoint.y > lowest)
		{
			lowest = tmppoint.y;
			
		}
	}
	return lowest;
}

int GPolyline::findleftest()
{
	POINT tmppoint;

	int leftest = 9999;

	for (int i = 0; i < this->m_polypoints.GetCount(); i++)
	{
		tmppoint = m_polypoints[i];

		if (tmppoint.x < leftest)
			leftest = tmppoint.x;
	}
	return leftest;
}
int GPolyline::findrightest()
{
	POINT tmppoint;

	int rightest = 0;

	for (int i = 0; i < this->m_polypoints.GetCount(); i++)
	{
		tmppoint = m_polypoints[i];

		if (tmppoint.x > rightest)
			rightest = tmppoint.x;
	}
	return rightest;
}

BOOL GPolyline::isInBound(CPoint point)
{
	if (this->findleftest() <= point.x && point.x <= this->findrightest() || this->findrightest() <= point.x && point.x <= this->findleftest()){
		if (this->findhighest() <= point.y && point.y <= this->findlowest() || this->findlowest() <= point.y && point.y <= this->findhighest()){
			
			return TRUE;
		}
	}
	return FALSE;
}


int GPolyline::getStartX(){ return this->findleftest(); }
int GPolyline::getStartY(){ return this->findhighest(); }

// statrtx = right / starty = high / endx = left / endy = low
void GPolyline::setSElected(BOOL selected)
{
	m_isSelected = selected;
}




void GPolyline::deletepolypointset(int){ m_polypoints.RemoveAt(1); }

GPolyline::~GPolyline()
{
}
