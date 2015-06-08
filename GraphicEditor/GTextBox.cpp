// GTextBox.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GTextBox.h"


// GTextBox



GTextBox::GTextBox()
{

}

void GTextBox::draw(CDC* dc)
{
	CRect rect;
	if (this->getStartX() > this->getEndX() && this->getStartY() > this->getEndY())
	{
		rect.SetRect(this->getEndX()+5, this->getEndY()+5, this->getStartX(), this->getStartY());
	}
	else
	{
		rect.SetRect(this->getStartX()+5, this->getStartY()+5, this->getEndX(), this->getEndY());
	}
	
	this->m_tmpstr.Copy(this->m_str);

	this->m_tmpstr.Add('\0');
	
	CPen pen(this->getPattern(), this->getThick(), this->getLineColor());
	dc->SelectObject(&pen);

	dc->Rectangle(this->getStartX(), this->getStartY(), this->getEndX(), this->getEndY());

	dc->DrawText(CString(this->m_str.GetData()), this->m_str.GetCount(), &rect, DT_WORDBREAK);

	this->m_tmpstr.RemoveAll();
}




int GTextBox::getEndX(){ return m_textendX; }
int GTextBox::getEndY(){ return m_textendY; }

void GTextBox::setEndX(int x){ m_textendX = x; }
void GTextBox::setEndY(int y){ m_textendY = y; }

void GTextBox::setEndXY(int x, int y){ m_textendX = x; m_textendY = y; }

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


