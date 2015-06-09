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
	//DDX_Control(pDX, IDC_Font, m_combofont);
	DDX_Control(pDX, IDC_LineThick, m_linethick);
	DDX_Control(pDX, IDC_LinePattern, m_linepattern);
	DDX_Control(pDX, IDC_FILLPATTERN, m_fillpattern);
	
}


BEGIN_MESSAGE_MAP(ControlEdit, CDialog)

	//ON_CBN_SELCHANGE(IDC_Font, &ControlEdit::OnCbnSelchangeFont)
END_MESSAGE_MAP()



/*
void ControlEdit::OnCbnSelchangeFont()
{
	m_fontnumb = m_combofont.GetCurSel();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
*/

BOOL ControlEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_combofont.SetCurSel(m_fontnumb);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
