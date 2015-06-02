
// GraphicEditorView.cpp : CGraphicEditorView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GraphicEditor.h"
#endif
#include "GraphicEditorDoc.h"
#include "GraphicEditorView.h"
#include "Rectangle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphicEditorView

IMPLEMENT_DYNCREATE(CGraphicEditorView, CFormView)

BEGIN_MESSAGE_MAP(CGraphicEditorView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_LINE, &CGraphicEditorView::OnLine)
	ON_COMMAND(ID_POLYLINE, &CGraphicEditorView::OnPolyline)
	ON_COMMAND(ID_RECTANGLE, &CGraphicEditorView::OnRectangle)
	ON_COMMAND(ID_ELLIPSE, &CGraphicEditorView::OnEllipse)
	ON_COMMAND(ID_TEXT, &CGraphicEditorView::OnText)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_UPDATE_COMMAND_UI(ID_TEXT, &CGraphicEditorView::OnUpdateText)
	ON_UPDATE_COMMAND_UI(ID_RECTANGLE, &CGraphicEditorView::OnUpdateRectangle)
	ON_UPDATE_COMMAND_UI(ID_POLYLINE, &CGraphicEditorView::OnUpdatePolyline)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CGraphicEditorView::OnUpdateEllipse)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CGraphicEditorView::OnUpdateLine)
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CGraphicEditorView 생성/소멸



CGraphicEditorView::CGraphicEditorView()
	: CFormView(CGraphicEditorView::IDD)
	, m_stringreg(_T(""))
{
	// TODO: 여기에 생성 코드를 추가합니다.
	//CurrentMode = DrawMode::LINE;								// 기본값은 라인

}

CGraphicEditorView::~CGraphicEditorView()
{
}

void CGraphicEditorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CGraphicEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CGraphicEditorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

}

void CGraphicEditorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGraphicEditorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGraphicEditorView 진단

#ifdef _DEBUG
void CGraphicEditorView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGraphicEditorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CGraphicEditorDoc* CGraphicEditorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicEditorDoc)));
	return (CGraphicEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicEditorView 메시지 처리기


void CGraphicEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	ldown = TRUE;
	CGraphicEditorDoc* pDoc = GetDocument();
	switch (CurrentMode)
	{
	case DrawMode::LINE:
		line.SetStart(point.x, point.y);
		pos = point;
		break;
	case DrawMode::RECT:{

		//line.SetStart(point.x, point.y);
		//line.SetEnd(point.x, point.y);
		//JRectangle* rect = new JRectangle(point, point);
		//pDoc->m_rects.Add(*rect);
		//pDoc->m_rectsCurrent = pDoc->m_rects.GetCount() - 1;
		break;
	}

	case DrawMode::TEXT:{
		line.SetStart(point.x, point.y);
		line.SetEnd(point.x, point.y);
		break;
	}
	default:
		break;
	}
	CFormView::OnLButtonDown(nFlags, point);
}



void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	ldown = FALSE;
	switch (CurrentMode)
	{
	case DrawMode::LINE:{
		line.SetEnd(point.x, point.y);
		CClientDC dc(this);
		dc.MoveTo(pos);
		dc.LineTo(point);
		//pos = point;
		break;
	}
	case DrawMode::RECT:{
		line.SetEnd(point.x, point.y);
		JRectangle r(line.getstart(), line.getend());
		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		dc.SetROP2(R2_COPYPEN);
		dc.Rectangle(r.getstart().x, r.getstart().y, r.getend().x, r.getend().y);
		break;
	}
	
	case DrawMode::TEXT:{
		
		
			line.SetEnd(point.x, point.y);
			JRectangle r(line.getstart(), line.getend());
			CClientDC dc(this);
			dc.SelectStockObject(NULL_BRUSH);
			dc.SetROP2(R2_COPYPEN);
			dc.Rectangle(r.getstart().x, r.getstart().y, r.getend().x, r.getend().y);

			//m_str.Add('\0');
			m_stringreg = CString(m_str.GetData());

			CPaintDC dt(this);

			//CString test = _T("this is test of textbox");
			dc.SetBkMode(TRANSPARENT);
			
			if (r.getstart().x > r.getend().x && r.getstart().y > r.getend().y)
			{
				dc.DrawText(_T("this is test of textbox"),
					CRect(r.getend().x, r.getend().y, r.getstart().x, r.getstart().y)
					, DT_LEFT | DT_WORDBREAK );
				
			}
			else{
			dc.DrawText(m_stringreg,
				CRect(r.getstart().x, r.getstart().y, r.getend().x, r.getend().y)
				, DT_LEFT | DT_WORDBREAK);
			}

			m_str.RemoveAll();
			
		break;
	}


	default:
		break;
	}
	CFormView::OnLButtonUp(nFlags, point);
}


void CGraphicEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (ldown){
		switch (CurrentMode)
		{
		case DrawMode::LINE:{
			CClientDC dc(this);
			
			dc.SetROP2(R2_NOT);
			
			///////////
			
			dc.MoveTo(pos);
			dc.LineTo(point);
			
			dc.SetROP2(R2_NOT);
			dc.MoveTo(pos);
			dc.LineTo(point);
			break;
		}
		case DrawMode::RECT:{
			CGraphicEditorDoc* pDoc = GetDocument();
			CClientDC dc(this);
			dc.SelectStockObject(NULL_BRUSH);
			dc.SetROP2(R2_NOT);
			dc.Rectangle(line.getstart().x, line.getstart().y, line.getend().x, line.getend().y);

			line.SetEnd(point.x, point.y);
			dc.Rectangle(line.getstart().x, line.getstart().y, line.getend().x, line.getend().y);		
		}
							
		default:
			break;
		}
		CFormView::OnMouseMove(nFlags, point);
	}
	
}
void CGraphicEditorView::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CurrentMode = DrawMode::LINE;
}


void CGraphicEditorView::OnPolyline()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CurrentMode = DrawMode::POLY;
}


void CGraphicEditorView::OnRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CurrentMode = DrawMode::RECT;
}


void CGraphicEditorView::OnEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CurrentMode = DrawMode::ELLP;
}


void CGraphicEditorView::OnText()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CurrentMode = DrawMode::TEXT;
}



void CGraphicEditorView::OnUpdateText(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(CurrentMode == DrawMode::TEXT);
}


void CGraphicEditorView::OnUpdateRectangle(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(CurrentMode == DrawMode::RECT);
}


void CGraphicEditorView::OnUpdatePolyline(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(CurrentMode == DrawMode::POLY);
}


void CGraphicEditorView::OnUpdateEllipse(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(CurrentMode == DrawMode::ELLP);
}


void CGraphicEditorView::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(CurrentMode == DrawMode::LINE);
}


void CGraphicEditorView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (CurrentMode)
	{
	case DrawMode::TEXT:{

		if (nChar == _T('\b')){
			if (m_str.GetSize() > 0)
				m_str.RemoveAt(m_str.GetSize() - 1);
		}

		else {
			m_str.Add(nChar);
		}

		break;
	}

	default:
		break;
	}
	CFormView::OnChar(nChar, nRepCnt, nFlags);
}
