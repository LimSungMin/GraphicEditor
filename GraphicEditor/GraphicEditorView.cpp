
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
#include "GEllipse.h"

// 컨트롤 에딧 헤더파일
#include "ControlEdit.h"

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
	ON_BN_CLICKED(IDC_LineColor, &CGraphicEditorView::OnBnClickedLinecolor)
	ON_BN_CLICKED(IDC_PaneColor, &CGraphicEditorView::OnBnClickedPanecolor)

	ON_COMMAND(ID_DELETE, &CGraphicEditorView::OnDelete)
	ON_COMMAND(ID_SELECT, &CGraphicEditorView::OnSelect)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CGraphicEditorView 생성/소멸



CGraphicEditorView::CGraphicEditorView()
	: CFormView(CGraphicEditorView::IDD)
	, m_stringreg(_T(""))
{
	// TODO: 여기에 생성 코드를 추가합니다.
	//CurrentMode = DrawMode::LINE;								// 기본값은 라인
	CurrentMode = DrawMode::NOTHING;
	ldown = TRUE;

	
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
	if (!(nFlags & MK_CONTROL)){ // Ctrl 키를 누르지 않고 클릭 -> 하나의 객체만 선택
		for (int i = 0; i < pDoc->vo.size(); i++)
			pDoc->vo[i]->setSelected(FALSE);

		switch (CurrentMode)
		{
		case DrawMode::LINE:
			//line.SetStart(point.x, point.y);
			pDoc->m_line = new GLine();

			pDoc->m_line->setStartX(point.x);
			pDoc->m_line->setStartY(point.y);
			pDoc->m_line->SetEnd(point);
			pDoc->m_line->setEndX(point.x);
			pDoc->m_line->setEndY(point.y);


			break;

		case DrawMode::ELLP:{
			pDoc->m_ellp = new GEllipse();

			pDoc->m_ellp->setStartX(point.x);
			pDoc->m_ellp->setStartY(point.y);
			pDoc->m_ellp->setEndX(point.x);
			pDoc->m_ellp->setEndY(point.y);
			pDoc->m_ellp->SetEnd(point);
		}

		case DrawMode::RECT:{

			pDoc->m_rect = new GRectangle();
			pDoc->m_rect->setPattern(PS_DOT);
			pDoc->m_rect->setLineColor(pDoc->m_colorLine);
			pDoc->m_rect->setFillColor(pDoc->m_colorFill);
			pDoc->m_rect->setStartX(point.x - 10);
			pDoc->m_rect->setStartY(point.y - 10);
			pDoc->m_rect->setEndX(point.x + 10);
			pDoc->m_rect->setEndY(point.y + 10);
			
			break;
		}

		case DrawMode::TEXT:{
			pDoc->m_text = new GTextBox();
			pDoc->m_text->setPattern(PS_DOT);
			pDoc->m_text->setLineColor(pDoc->m_colorLine);
			pDoc->m_text->setFillColor(pDoc->m_colorFill);
			pDoc->m_text->setStartX(point.x - 10);
			pDoc->m_text->setStartY(point.y - 10);
			pDoc->m_text->setEndX(point.x + 10);
			pDoc->m_text->setEndY(point.y + 10);

			break;
		}

		case DrawMode::POLY:{

			if (m_firstclick == TRUE){
				pDoc->m_poly = new GPolyline();

				m_firstclick = FALSE;
			}

			pDoc->m_poly->polypointset(point);

			break;
		}
		default:{ // DrawMode::NOTHING
			if (pDoc->vo.size() > 0 && m_currentSelected >= 0){
				if ((m_changeSizePosition = pDoc->vo[m_currentSelected]->isInSizeBound(point)) >= 0){ // 크기 조절 위치는 0~3

					if (pDoc->vo[m_currentSelected] == pDoc->m_poly){ // 폴리라인의 경우 특수하므로 바꾸어야됨
						//MessageBox(NULL, NULL, NULL);

						pDoc->vo[m_currentSelected]->polypointmovecheck(1);

						polypointmove = TRUE;
						m_changeSize = TRUE;
						pDoc->vo[m_currentSelected]->setSelected(TRUE);
						polypointindex = m_changeSizePosition;
						break;
					}

					m_changeSize = TRUE;
					pDoc->vo[m_currentSelected]->setSelected(TRUE);
					return;
				}
			}
			for (int i = 0; i < pDoc->vo.size(); i++) // 선택되었던 객체를 전부 선택 해제한다.
				pDoc->vo[i]->setSelected(FALSE);
			m_group.group.RemoveAll();
			for (int i = pDoc->vo.size() - 1; i >= 0; i--){ // 맨 위에 있는 도형을 잡기 위해 역순으로 검사함.
				if (pDoc->vo[i]->isInBound(point)){
					m_move = TRUE;
					pDoc->vo[i]->setSelected(TRUE);
					m_currentSelected = i;
					m_group.group.Add(i);
					m_clickedPoint = point;
					Invalidate(FALSE);
					return;
				}
			}
			// 여기서부턴 누른 지점에 도형이 없을 때.
			m_currentSelected = -1;
			break;
		}

		}
	}
	else{ // Ctrl키를 누른 상태로 클릭 => 다중 선택 필요!
		
		for (int i = pDoc->vo.size() - 1; i >= 0; i--){ // 맨 위에 있는 도형을 잡기 위해 역순으로 검사함.
			if (pDoc->vo[i]->isInBound(point)){
				GObject* ptr = pDoc->vo[i];
				if (pDoc->vo[i]->getSelected() == FALSE){
					pDoc->vo[i]->setSelected(TRUE);
					//m_group.group.Add(i);
					MessageBeep(0);
				}
				else{
					//pDoc->vo[i]->setSelected(FALSE);
					//m_group.group.RemoveAt(0);
				}
				
				//m_move = TRUE;
				
				//m_currentSelected = i;
				m_clickedPoint = point;
				
				Invalidate();
				return;
			}
		}
	}
	Invalidate();
	CFormView::OnLButtonDown(nFlags, point);
}



void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CGraphicEditorDoc* pDoc = GetDocument();
	ldown = FALSE;
	if (m_changeSize == TRUE){
		m_changeSize = FALSE;
		m_changeSizePosition = -1;
		pDoc->vo[m_currentSelected]->setSelected(TRUE);
		return;
	}

	GLine line;
	switch (CurrentMode)
	{
	case DrawMode::LINE:{
		pDoc->m_line->setPattern(PS_SOLID);
		pDoc->m_line->setSelected(TRUE);
		pDoc->vo.push_back(pDoc->m_line);
		m_currentSelected = pDoc->vo.size() - 1;
		Invalidate();
		break;
	}
						
	case DrawMode::ELLP:{
		pDoc->m_ellp->setPattern(PS_SOLID);
		pDoc->m_ellp->setSelected(TRUE);
		pDoc->vo.push_back(pDoc->m_ellp);
		m_currentSelected = pDoc->vo.size() - 1;
		Invalidate();
		break;
	}
	case DrawMode::RECT:{
		pDoc->m_rect->setPattern(PS_SOLID);
		pDoc->m_rect->setSelected(TRUE);
		pDoc->vo.push_back(pDoc->m_rect);
		m_currentSelected = pDoc->vo.size() - 1;
		Invalidate();
		break;
	}
	
	case DrawMode::TEXT:{
		pDoc->m_text->setPattern(PS_SOLID);
		pDoc->m_text->setSelected(TRUE);
		pDoc->vo.push_back(pDoc->m_text);
		m_currentSelected = pDoc->vo.size() - 1;
		Invalidate();
		
		break;
	}
	case DrawMode::POLY:{

		pDoc->vo.push_back(pDoc->m_poly);
		//m_currentSelected = pDoc->vo.size() - 1;
		Invalidate();
		break;
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

	int index;
	if (!(nFlags&MK_CONTROL)){ // Ctrl키가 눌려 있지 않을 때.
		if (ldown){ // 왼쪽 버튼이 눌려 있어야만 끌려야 하니까.
			if (m_changeSize == TRUE){ // 크기 변경 사각형을 눌렀을 때.
				if (pDoc->vo[m_currentSelected] == pDoc->m_poly){
					pDoc->vo[m_currentSelected]->polypointmovecheck(1);
					if (pDoc->vo[m_currentSelected]->isInSizeBound(point) < 0){
						index = polypointindex;
					}
					else
						index = pDoc->vo[m_currentSelected]->isInSizeBound(point);
					pDoc->vo[m_currentSelected]->pointmover(point.x, point.y, index);
					//m_changeSizePosition = pDoc->vo[m_currentSelected]->isInSizeBound(point) // 몇번째 네모인지 확인
				}
				else{ // Polyline이 아닐 때. 즉, 일반적인 도형의 끄트머리를 잡고 움직일 때.
					switch (m_changeSizePosition){
					case 0:{ // 왼쪽 위
						pDoc->vo[m_currentSelected]->setStartX(point.x);
						pDoc->vo[m_currentSelected]->setStartY(point.y);
						break;
					}
					case 1:{ // 오른쪽 위
						pDoc->vo[m_currentSelected]->setEndX(point.x);
						pDoc->vo[m_currentSelected]->setStartY(point.y);
						break;
					}
					case 2:{ // 왼쪽 아래
						pDoc->vo[m_currentSelected]->setStartX(point.x);
						pDoc->vo[m_currentSelected]->setEndY(point.y);
						break;
					}
					case 3:{ // 오른쪽 아래
						pDoc->vo[m_currentSelected]->setEndX(point.x);
						pDoc->vo[m_currentSelected]->setEndY(point.y);
						break;
					}
					default:{
						break;
					}
					}
				}
				Invalidate();
				return;
			}
			
			switch (CurrentMode)
			{
			case DrawMode::LINE:{
				pDoc->m_line->SetEnd(point);
				pDoc->m_line->setEndX(point.x);
				pDoc->m_line->setEndY(point.y);
				Invalidate();
				break;
			}
			case DrawMode::ELLP:{
				pDoc->m_ellp->SetEnd(point);
				pDoc->m_ellp->setEndX(point.x);
				pDoc->m_ellp->setEndY(point.y);
				Invalidate();
				break;
			}


			case DrawMode::RECT:{
				pDoc->m_rect->setEndX(point.x);
				pDoc->m_rect->setEndY(point.y);
				Invalidate(FALSE);

				break;
			}
								
			case DrawMode::TEXT:{
				pDoc->m_text->setEndXY(point.x, point.y);
				
				Invalidate();
				break;
				
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

					Invalidate(FALSE);
				}
				break;
			}
			}
			CFormView::OnMouseMove(nFlags, point);
		}
	}
	else{ // Ctrl이 눌려있을 때. pDoc->m_group을 돌면서 이동을 시켜야 함.
		if (ldown){
			int startX, startY, endX, endY;
			for (int i = 0; i < pDoc->vo.size();i++){
				if (pDoc->vo[i]->getSelected() == TRUE){
					//CString str;
					//str.Format(_T("%d"), i);
					//MessageBox(str, _T("test"), MB_OK);
					/*GObject* curr = pDoc->vo[i];

					int startX = curr->getStartX();
					int startY = curr->getStartY();
					int endX = curr->getEndX();
					int endY = curr->getEndY();

					startX += point.x - m_clickedPoint.x;
					startY += point.y - m_clickedPoint.y;
					endX += point.x - m_clickedPoint.x;
					endY += point.y - m_clickedPoint.y;

					curr->move(startX, startY, endX, endY);
					m_clickedPoint = point;*/
					
					startX = pDoc->vo[i]->getStartX();
					startY = pDoc->vo[i]->getStartY();
					endX = pDoc->vo[i]->getEndX();
					endY = pDoc->vo[i]->getEndY();

					startX += point.x - m_clickedPoint.x;
					startY += point.y - m_clickedPoint.y;
					endX += point.x - m_clickedPoint.x;
					endY += point.y - m_clickedPoint.y;

					pDoc->vo[i]->move(startX, startY, endX, endY);
					
				}
			}
			m_clickedPoint = point;
			Invalidate(FALSE);
		}
	}
	
}
void CGraphicEditorView::OnLine()
{
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

void CGraphicEditorView::OnDraw(CDC* pDC)
{
	
	CString str;
	CGraphicEditorDoc* pDoc = GetDocument();

	CBrush brush(RGB(255, 255, 255));
	pDC->SelectObject(&brush);
	pDC->Rectangle(0,0,10000,10000);

	for (auto i : pDoc->vo) i->draw(pDC);
	
	switch (CurrentMode){
	case DrawMode::LINE:{
		pDoc->m_line->draw(pDC);
		
		break;
	}
	case DrawMode::ELLP:{
		pDoc->m_ellp->draw(pDC);
		break;
	}
	case DrawMode::RECT:{
		pDoc->m_rect->draw(pDC);
		
		break;
		}

	case DrawMode::POLY:{
		pDoc->m_poly->draw(pDC);
		break;
	}
	case DrawMode::TEXT:{
		pDoc->m_text->draw(pDC);
	}
	
	}
	
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}



void CGraphicEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CGraphicEditorDoc* pDoc = GetDocument();
	
	if (m_firstclick = FALSE)
	pDoc->m_poly->polypointset(point);
	m_firstclick = TRUE;
	

	//pDoc->m_poly->deletepolypointset(1);
	//pDoc->m_polypoints.Add(NULL);
	//
	CFormView::OnLButtonDblClk(nFlags, point);
}


void CGraphicEditorView::OnEditUndo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGraphicEditorDoc* pDoc = GetDocument();
	Invalidate(FALSE);
	pDoc->vo.pop_back();
	Invalidate(FALSE);
}


void CGraphicEditorView::OnBnClickedLinecolor() // 선 색 설정을 불러옴
{
	CColorDialog cdlg;
	CGraphicEditorDoc* pDoc = GetDocument();
	


	if (cdlg.DoModal() == IDOK)
	{
		if (m_currentSelected >= 0){
			GObject* curr = pDoc->vo[m_currentSelected];
			curr->setLineColor(cdlg.GetColor());
		}
		pDoc->m_colorLine = cdlg.GetColor();
		Invalidate(FALSE);
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnBnClickedPanecolor()
{
	CColorDialog cdlg;
	CGraphicEditorDoc* pDoc = GetDocument();

	if (cdlg.DoModal() == IDOK)
	{
		if (m_currentSelected >= 0){
			GObject* curr = pDoc->vo[m_currentSelected];
			curr->setFillColor(cdlg.GetColor());
		}
		pDoc->m_colorFill = cdlg.GetColor();
		Invalidate(FALSE);
	}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

// 삭제 함수 입니다.
void CGraphicEditorView::OnDelete()
{
	CGraphicEditorDoc* pDoc = GetDocument();
	if (pDoc->vo.size() > 0 && m_currentSelected != -1){
		
		pDoc->vo.erase((pDoc->vo.begin() + m_currentSelected));
		m_currentSelected = -1;
	}
	Invalidate(FALSE);
}


void CGraphicEditorView::OnSelect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGraphicEditorDoc* pDoc = GetDocument();
	CurrentMode = DrawMode::NOTHING;				// 드로우 모드를 NOTHING 으로
	for (auto i : pDoc->vo) i->setSelected(false);	// 모든 객체의 선택을 해제한다
	Invalidate(FALSE);
}


BOOL CGraphicEditorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CFormView::OnEraseBkgnd(pDC);
	return TRUE;
}
