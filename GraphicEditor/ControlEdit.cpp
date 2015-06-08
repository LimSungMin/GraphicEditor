// ControlEdit.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GraphicEditor.h"
#include "ControlEdit.h"
#include "afxdialogex.h"
#include "GraphicEditorDoc.h"

// ControlEdit 대화 상자입니다.

IMPLEMENT_DYNAMIC(ControlEdit, CDialog)

ControlEdit::ControlEdit(CWnd* pParent /*=NULL*/)
	: CDialog(ControlEdit::IDD, pParent)
{

}

ControlEdit::~ControlEdit()
{
}

void ControlEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Font, m_combofont);
}


BEGIN_MESSAGE_MAP(ControlEdit, CDialog)

	ON_CBN_SELCHANGE(IDC_Font, &ControlEdit::OnCbnSelchangeFont)
END_MESSAGE_MAP()




void ControlEdit::OnCbnSelchangeFont()
{
	m_fontnumb = m_combofont.GetCurSel();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
