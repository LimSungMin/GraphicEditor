#include "stdafx.h"
#include "GRectangle.h"


GRectangle::GRectangle() : GObject(0, 0), m_endX(0), m_endY(0)
{
	this->setPattern(PS_DOT);
}

GRectangle::GRectangle(int x1, int y1, int x2, int y2) : GObject(x1, y1), m_endX(x2), m_endY(y2)
{

}

void GRectangle::draw(CDC* dc){
	CPen pen(this->getPattern(), this->getThick(), this->getLineColor());
	dc->SelectObject(&pen);
	dc->SelectStockObject(NULL_BRUSH);
	dc->Rectangle(this->getStartX(), this->getStartY(), this->getEndX(), this->getEndY());
	if (this->getSelected() == TRUE){
		CBrush brush(RGB(255, 255, 255));
		dc->SelectObject(&brush);
		m_selectedRect[0] = new CRect(this->getStartX() - 5, this->getStartY() - 5, this->getStartX() + 5, this->getStartY() + 5);
		m_selectedRect[1] = new CRect(this->getEndX() - 5, this->getStartY() - 5, this->getEndX() + 5, this->getStartY() + 5);
		m_selectedRect[2] = new CRect(this->getStartX() - 5, this->getEndY() - 5, this->getStartX() + 5, this->getEndY() + 5);
		m_selectedRect[3] = new CRect(this->getEndX() - 5, this->getEndY() - 5, this->getEndX() + 5, this->getEndY() + 5); // 메모리 누수의 위험 있음. 수정바람!
		dc->Rectangle(m_selectedRect[0]);
		dc->Rectangle(m_selectedRect[1]);
		dc->Rectangle(m_selectedRect[2]);
		dc->Rectangle(m_selectedRect[3]);


	}
}

int GRectangle::getEndX(){ return m_endX; }
int GRectangle::getEndY(){ return m_endY; }

void GRectangle::setEndX(int x){ m_endX = x; }
void GRectangle::setEndY(int y){ m_endY = y; }

BOOL GRectangle::isInBound(CPoint point){
	if (this->getStartX() <= point.x && point.x <= this->getEndX() || this->getEndX() <= point.x && point.x <= this->getStartX()){
		if (this->getStartY() <= point.y && point.y <= this->getEndY() || this->getEndY() <= point.y && point.y <= this->getStartY()){
			return TRUE;
		}
	}
	return FALSE;
}

int GRectangle::isInSizeBound(CPoint point){
	for (int i = 0; i < 4; i++){
		if (this->m_selectedRect[i]->left <= point.x && point.x <= this->m_selectedRect[i]->right || this->m_selectedRect[i]->right <= point.x && point.x <= this->m_selectedRect[i]->left){
			if (this->m_selectedRect[i]->top <= point.y && point.y <= this->m_selectedRect[i]->bottom || this->m_selectedRect[i]->bottom <= point.y && point.y <= this->m_selectedRect[i]->top){
				
				return i;
			}
		}
	}
	/*if (this->m_selectedRect[0]->left <= point.x && point.x <= this->m_selectedRect[0]->right || this->m_selectedRect[0]->right <= point.x && point.x <= this->m_selectedRect[0]->left){
	if (this->m_selectedRect[0]->top <= point.y && point.y <= this->m_selectedRect[0]->bottom || this->m_selectedRect[0]->bottom <= point.y && point.y <= this->m_selectedRect[0]->top){
	MessageBeep(NULL);
	return 0;
	}
	}*/
	return -1;
}

void GRectangle::move(int x1, int y1, int x2, int y2){
	this->setStartX(x1);
	this->setStartY(y1);
	this->setEndX(x2);
	this->setEndY(y2);
}

void GRectangle::setSelected(BOOL selected){
	m_isSelected = selected;

}

GRectangle::~GRectangle()
{
	delete[] m_selectedRect;
}
