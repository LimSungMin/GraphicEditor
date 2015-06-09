// GTextBox.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GTextBox.h"



GTextBox::GTextBox()
{
	m_fontsize = 100;
}

void GTextBox::draw(CDC* dc)
{
	////////////////////////////////////////////////////////////////////////////////////////////////// 글씨를 출력 
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

	//this->m_tmpstr.Add('\0');
	
	CPen pen(this->getPattern(), this->getThick(), this->getLineColor());
	
	dc->SelectObject(&pen);
	CBrush brush(this->getFillColor());

	dc->SelectObject(&brush);
	dc->Rectangle(this->getStartX(), this->getStartY(), this->getEndX(), this->getEndY());
	
	
	CFont font;
	CString fontname;

	if (this->m_font == 0)
	{
		fontname = _T("굴림");
	}
	else if (this->m_font == 1)
	{
		fontname = _T("궁서");
	}
	else if (this->m_font == 2)
	{
		fontname = _T("바탕");
	}
	HDC hdc = 0;

	if (this->m_fontsize == 1)
		MessageBeep(1);

	if ( first == TRUE)
		font.CreatePointFont(100, fontname);

	else if (first == FALSE)
	font.CreatePointFont(this->getFontSize(), fontname);




	//font.CreatePointFont(100*2, fontname);
	dc->SelectObject(&font);
	dc->SetTextColor(this->getFontColor());
	dc->SetBkMode(TRANSPARENT);
	//SetBkMode(hdc, TRANSPARENT);

	int sortflag = DT_RIGHT;

	//SetTextColor(hdc, this->getFontColor());
	dc->DrawText(CString(this->m_str.GetData()), this->m_str.GetCount(), &rect,  DT_WORDBREAK | this->getFontSort());// | TRANSPARENT);

	

	this->m_tmpstr.RemoveAll();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 선택시 주변 사각형 출력 
	if ( this->getSelected() == TRUE){
		
		m_selectedRect[0] = new CRect(this->getStartX() - 5, this->getStartY() - 5, this->getStartX() + 5, this->getStartY() + 5);
		m_selectedRect[1] = new CRect(this->getEndX() - 5, this->getStartY() - 5, this->getEndX() + 5, this->getStartY() + 5);
		m_selectedRect[2] = new CRect(this->getStartX() - 5, this->getEndY() - 5, this->getStartX() + 5, this->getEndY() + 5);
		m_selectedRect[3] = new CRect(this->getEndX() - 5, this->getEndY() - 5, this->getEndX() + 5, this->getEndY() + 5); // 메모리 누수의 위험 있음. 수정바람!

		CPen pen3(PS_SOLID, 1, RGB(0, 0, 0));
		CBrush brush3(RGB(255, 255,255));
		dc->SelectObject(pen3);
		dc->SelectObject(brush3);
		for (int i = 0; i < 4; i++)
		{
			dc->Rectangle(m_selectedRect[i]);
		}

	}
	
}

/////////////////////////////////////////////////////


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


