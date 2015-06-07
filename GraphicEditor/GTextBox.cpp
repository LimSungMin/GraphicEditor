// GTextBox.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GTextBox.h"


// GTextBox



GTextBox::GTextBox()
{

}




int GTextBox::getEndX(){ return m_endX; }
int GTextBox::getEndY(){ return m_endY; }

void GTextBox::setEndX(int x){ m_endX = x; }
void GTextBox::setEndY(int y){ m_endY = y; }

void GTextBox::move(int x1, int y1, int x2, int y2){
	this->setStartX(x1);
	this->setStartY(y1);
	this->setEndX(x2);
	this->setEndY(y2);
}


void GTextBox::setSelected(BOOL selected){
	m_isSelected = selected;

}

BOOL GTextBox::isInBound(CPoint point){
	if (this->getStartX() <= point.x && point.x <= this->getEndX() || this->getEndX() <= point.x && point.x <= this->getStartX()){
		if (this->getStartY() <= point.y && point.y <= this->getEndY() || this->getEndY() <= point.y && point.y <= this->getStartY()){
			return TRUE;
		}
	}
	return FALSE;
}

int GTextBox::isInSizeBound(CPoint point){
	for (int i = 0; i < 4; i++){
		if (this->m_selectedRect[i]->left <= point.x && point.x <= this->m_selectedRect[i]->right || this->m_selectedRect[i]->right <= point.x && point.x <= this->m_selectedRect[i]->left){
			if (this->m_selectedRect[i]->top <= point.y && point.y <= this->m_selectedRect[i]->bottom || this->m_selectedRect[i]->bottom <= point.y && point.y <= this->m_selectedRect[i]->top){

				return i;
			}
		}
	}
	
	return -1;
}


GTextBox::~GTextBox()
{
}






// GTextBox 메시지 처리기입니다.


