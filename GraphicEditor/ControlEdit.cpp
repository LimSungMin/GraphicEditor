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
}


BEGIN_MESSAGE_MAP(ControlEdit, CDialog)

END_MESSAGE_MAP()


