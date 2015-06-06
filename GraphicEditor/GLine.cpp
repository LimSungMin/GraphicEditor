#include "stdafx.h"
#include "GLine.h"


GLine::GLine() : GObject(0, 0), m_endX(0), m_endY(0)	
{	
	this->setPattern(PS_DOT);
}


GLine::~GLine() 
{
	//delete[] m_selectedRect;
}

void GLine::draw(CDC* dc){
	CPen pen(this->getPattern(), this->getThick(), this->getLineColor());
	dc->SelectObject(&pen);
	dc->SelectStockObject(NULL_BRUSH);
	// 선 그리기는 여기서부터
	dc->MoveTo(getStartX(), getStartY());
	dc->LineTo(GetEnd());		
	
	if (this->getSelected()){
		CBrush brush(RGB(255, 255, 255));
		dc->SelectObject(brush);
		m_selectedRect[0] = new CRect(this->getStartX() - 5, this->getStartY() - 5, this->getStartX() + 5, this->getStartY() + 5);
		m_selectedRect[1] = new CRect(this->GetEnd().x - 5, this->GetEnd().y - 5, this->GetEnd().x + 5, this->GetEnd().y + 5);

		dc->Rectangle(m_selectedRect[0]);
		dc->Rectangle(m_selectedRect[1]);
	}
}

BOOL GLine::isInBound(CPoint point){
	/*
	if (this->getStartX() <= point.x && point.x <= this->getEndX() || this->getEndX() <= point.x && point.x <= this->getStartX()){
		if (this->getStartY() <= point.y && point.y <= this->getEndY() || this->getEndY() <= point.y && point.y <= this->getStartY()){
			return TRUE;
		}
	}*/
	if (getStartX() <= point.x && point.x <= getEndX() && getStartY() <= point.y && point.y <= getEndY()) return TRUE;
	if (getEndX() <= point.x && point.x <= getStartX() && getEndY() <= point.y && point.y <= getStartY()) return TRUE;
	return FALSE;
}

int GLine::isInSizeBound(CPoint point){
	for (int i = 0; i < 2; i++){
		if (this->m_selectedRect[i]->left <= point.x && point.x <= this->m_selectedRect[i]->right || this->m_selectedRect[i]->right <= point.x && point.x <= this->m_selectedRect[i]->left){
			if (this->m_selectedRect[i]->top <= point.y && point.y <= this->m_selectedRect[i]->bottom || this->m_selectedRect[i]->bottom <= point.y && point.y <= this->m_selectedRect[i]->top){
				MessageBeep(NULL);
				if (i == 0) return 0;
				else if (i == 1) return 3;
			}
		}
	}

	return -1;
}

void GLine::move(int x1, int y1, int x2, int y2){
	this->setStartX(x1);
	this->setStartY(y1);
	this->setEndX(x2);
	this->setEndY(y2);
}

void GLine::setSelected(BOOL selected){
	m_isSelected = selected;

}

void GLine::SetEnd(POINT point){
	m_endX = point.x;
	m_endY = point.y;	
}
POINT GLine::GetEnd(){
	POINT value;
	value.x = m_endX;
	value.y = m_endY;
	return value;
}
int GLine::getEndX(){ return m_endX; }
int GLine::getEndY(){ return m_endY; }

void GLine::setEndX(int x){ m_endX = x; }
void GLine::setEndY(int y){ m_endY = y; }