
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
//#include "Rectangle.h"
#include "GObject.h"
#include "GRectangle.h"
#include "GPolyline.h"
#include "GLine.h"

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
//	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_EDIT_UNDO, &CGraphicEditorView::OnEditUndo)
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
		//line.SetStart(point.x, point.y);
		pDoc->m_line = new GLine();

		pDoc->m_line->setStartX(point.x);
		pDoc->m_line->setStartY(point.y);
		pDoc->m_line->SetEnd(point);



		pos = point;
		break;
	case DrawMode::RECT:{
		pDoc->m_rect = new GRectangle();
		pDoc->m_rect->setPattern(PS_DOT);
		pDoc->m_rect->setStartX(point.x - 10);
		pDoc->m_rect->setStartY(point.y - 10);
		pDoc->m_rect->setEndX(point.x + 10);
		pDoc->m_rect->setEndY(point.y + 10);
		Invalidate();
		break;
	}

	case DrawMode::TEXT:{
		//line.SetStart(point.x, point.y);
		//line.SetEnd(point.x, point.y);
		break;
	}

	case DrawMode::POLY:{

		pDoc->m_poly.polypointset(point);
	}
	default:{ // DrawMode::NOTHING
		for (int i = pDoc->vo.size()-1; i >=0; i--){ // 맨 위에 있는 도형을 잡기 위해 역순으로 검사함.
			if (pDoc->vo[i]->isInBound(point)){
				m_move = TRUE;
				pDoc->vo[i]->setSelected(TRUE);
				m_currentSelected = i;
				m_clickedPoint = point;
				return;
			}
		}

		break;
	}
	}
	CFormView::OnLButtonDown(nFlags, point);
}



void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CGraphicEditorDoc* pDoc = GetDocument();
	ldown = FALSE;
	GLine line;
	switch (CurrentMode)
	{
	case DrawMode::LINE:{
		pDoc->vo.push_back(pDoc->m_line);
		break;
	}
	case DrawMode::RECT:{
		pDoc->m_rect->setPattern(PS_SOLID);
		pDoc->vo.push_back(pDoc->m_rect);
		Invalidate();
		break;
	}
	
	case DrawMode::TEXT:{
		
		/*
			line.SetEnd(point.x, point.y);
			//JRectangle r(line.getstart(), line.getend());
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
			*/
		break;
	}
	case DrawMode::POLY:{
		Invalidate();
	}
	default:
		m_move = FALSE;
		break;
	}

	CFormView::OnLButtonUp(nFlags, point);
}


void CGraphicEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CGraphicEditorDoc* pDoc = GetDocument();

	if (ldown){
		switch (CurrentMode)
		{
		case DrawMode::LINE:{
			pDoc->m_line->SetEnd(point);
			Invalidate();
			break;
		}
		case DrawMode::RECT:{
			pDoc->m_rect->setEndX(point.x);
			pDoc->m_rect->setEndY(point.y);
			Invalidate();
		}
		default:{
			if (m_move == TRUE){ // 객체가 선택되었을 때 도형을 잡고 움직이는 상황
				GObject* curr = pDoc->vo[m_currentSelected];
				
				int startX = curr->getStartX();
				int startY = curr->getStartY();
				int endX = curr->getEndX();
				int endY = curr->getEndY();

				startX += point.x - m_clickedPoint.x;
				startY += point.y - m_clickedPoint.y;
				endX += point.x - m_clickedPoint.x;
				endY += point.y - m_clickedPoint.y;
				
				curr->move(startX, startY, endX, endY);
				m_clickedPoint = point;
				Invalidate();
			}
			break;
		}
		}
		CFormView::OnMouseMove(nFlags, point);
	}
	
}
void CGraphicEditorView::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (CurrentMode != DrawMode::LINE)
		CurrentMode = DrawMode::LINE;
	else
		CurrentMode = DrawMode::NOTHING;
}


void CGraphicEditorView::OnPolyline()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (CurrentMode != DrawMode::POLY)
	CurrentMode = DrawMode::POLY;
	else
		CurrentMode = DrawMode::NOTHING;
}


void CGraphicEditorView::OnRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (CurrentMode != DrawMode::RECT)
		CurrentMode = DrawMode::RECT;
	else
		CurrentMode = DrawMode::NOTHING;
}


void CGraphicEditorView::OnEllipse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (CurrentMode != DrawMode::ELLP)
	CurrentMode = DrawMode::ELLP;
	else
		CurrentMode = DrawMode::NOTHING;
}


void CGraphicEditorView::OnText()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (CurrentMode != DrawMode::TEXT)
	CurrentMode = DrawMode::TEXT;
	else
		CurrentMode = DrawMode::NOTHING;
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
int i = 0;

void CGraphicEditorView::OnDraw(CDC* pDC)
{
	
	CString str;
	CGraphicEditorDoc* pDoc = GetDocument();


	/*for (int i = 0; i < pDoc->m_shapes.GetCount(); i++){
		pDoc->m_shapes[i].draw(pDC);
	}
	pDoc->m_poly.draw(pDC);*/
	

	for (auto i : pDoc->vo) i->draw(pDC); // 저장된 모든 도형 객체 출력

	switch (CurrentMode){
	case DrawMode::LINE:{
		pDoc->m_line->draw(pDC);
		
		break;
	}
	case DrawMode::RECT:{
		pDoc->m_rect->draw(pDC);
		
		break;
		}

	case DrawMode::POLY:{
		pDoc->m_poly.draw(pDC);
		break;
	}
	
	}
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}



void CGraphicEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CGraphicEditorDoc* pDoc = GetDocument();

	//pDoc->m_polypoints.Add(NULL);

	CFormView::OnLButtonDblClk(nFlags, point);
}


void CGraphicEditorView::OnEditUndo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGraphicEditorDoc* pDoc = GetDocument();
	Invalidate();
	pDoc->vo.pop_back();
	Invalidate();
}
