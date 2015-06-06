
// GraphicEditorView.cpp : CGraphicEditorView Å¬·¡½ºÀÇ ±¸Çö
//

#include "stdafx.h"
// SHARED_HANDLERS´Â ¹Ì¸® º¸±â, Ãà¼ÒÆÇ ±×¸² ¹× °Ë»ö ÇÊÅÍ Ã³¸®±â¸¦ ±¸ÇöÇÏ´Â ATL ÇÁ·ÎÁ§Æ®¿¡¼­ Á¤ÀÇÇÒ ¼ö ÀÖÀ¸¸ç
// ÇØ´ç ÇÁ·ÎÁ§Æ®¿Í ¹®¼­ ÄÚµå¸¦ °øÀ¯ÇÏµµ·Ï ÇØ Áİ´Ï´Ù.
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

// CGraphicEditorView »ı¼º/¼Ò¸ê



CGraphicEditorView::CGraphicEditorView()
	: CFormView(CGraphicEditorView::IDD)
	, m_stringreg(_T(""))
{
	// TODO: ¿©±â¿¡ »ı¼º ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	//CurrentMode = DrawMode::LINE;								// ±âº»°ªÀº ¶óÀÎ

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
	// TODO: CREATESTRUCT cs¸¦ ¼öÁ¤ÇÏ¿© ¿©±â¿¡¼­
	//  Window Å¬·¡½º ¶Ç´Â ½ºÅ¸ÀÏÀ» ¼öÁ¤ÇÕ´Ï´Ù.

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


// CGraphicEditorView Áø´Ü

#ifdef _DEBUG
void CGraphicEditorView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGraphicEditorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CGraphicEditorDoc* CGraphicEditorView::GetDocument() const // µğ¹ö±×µÇÁö ¾ÊÀº ¹öÀüÀº ÀÎ¶óÀÎÀ¸·Î ÁöÁ¤µË´Ï´Ù.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicEditorDoc)));
	return (CGraphicEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicEditorView ¸Ş½ÃÁö Ã³¸®±â


void CGraphicEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ¿©±â¿¡ ¸Ş½ÃÁö Ã³¸®±â ÄÚµå¸¦ Ãß°¡ ¹×/¶Ç´Â ±âº»°ªÀ» È£ÃâÇÕ´Ï´Ù.
	ldown = TRUE;
	CGraphicEditorDoc* pDoc = GetDocument();
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


		
		pos = point;
		break;
	case DrawMode::ELLP:{
		pDoc->m_ellp = new GEllipse();
		pDoc->m_ellp->setStartX(point.x);
		pDoc->m_ellp->setStartY(point.y);
		pDoc->m_ellp->SetEnd(point);
	}
	case DrawMode::RECT:{
		pDoc->m_rect = new GRectangle();
		pDoc->m_rect->setPattern(PS_DOT);
		pDoc->m_rect->setStartX(point.x - 10);
		pDoc->m_rect->setStartY(point.y - 10);
		pDoc->m_rect->setEndX(point.x + 10);
		pDoc->m_rect->setEndY(point.y + 10);
		//Invalidate();
		break;
	}

	case DrawMode::TEXT:{
		//line.SetStart(point.x, point.y);
		//line.SetEnd(point.x, point.y);
		break;
	}

	case DrawMode::POLY:{
		
		//pDoc->m_poly.polypointset(point);
		}
		// Çª½Ã°¡ µÇ¾ú´ÂÁö È®ÀÎÇÑ´Ù 
		pDoc->m_poly->polypointset(point);
	default:{ // DrawMode::NOTHING
		if (pDoc->vo.size()>0 && m_currentSelected >= 0){
			if ((m_changeSizePosition = pDoc->vo[m_currentSelected]->isInSizeBound(point)) >= 0 ){ // Å©±â Á¶Àı À§Ä¡´Â 0~3
				m_changeSize = TRUE;
				pDoc->vo[m_currentSelected]->setSelected(TRUE);
				return;
			}
		}
		for (int i = 0; i < pDoc->vo.size(); i++) // ¼±ÅÃµÇ¾ú´ø °´Ã¼¸¦ ÀüºÎ ¼±ÅÃ ÇØÁ¦ÇÑ´Ù.
			pDoc->vo[i]->setSelected(FALSE);

		for (int i = pDoc->vo.size()-1; i >=0; i--){ // ¸Ç À§¿¡ ÀÖ´Â µµÇüÀ» Àâ±â À§ÇØ ¿ª¼øÀ¸·Î °Ë»çÇÔ.
			if (pDoc->vo[i]->isInBound(point)){
				m_move = TRUE;
				pDoc->vo[i]->setSelected(TRUE);
				m_currentSelected = i;
				m_clickedPoint = point;
				break;
	}
		}
		break;
	}
	}
	Invalidate();
	CFormView::OnLButtonDown(nFlags, point);
}



void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ¿©±â¿¡ ¸Ş½ÃÁö Ã³¸®±â ÄÚµå¸¦ Ãß°¡ ¹×/¶Ç´Â ±âº»°ªÀ» È£ÃâÇÕ´Ï´Ù.
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
		pDoc->vo.push_back(pDoc->m_line);
		break;
	}
	case DrawMode::ELLP:{
		pDoc->vo.push_back(pDoc->m_ellp);
		break;
	}
	case DrawMode::RECT:{
		pDoc->m_rect->setPattern(PS_SOLID);
		pDoc->m_rect->setSelected(TRUE);
		pDoc->vo.push_back(pDoc->m_rect);
		m_currentSelected = pDoc->vo.size()-1;
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
	// TODO: ¿©±â¿¡ ¸Ş½ÃÁö Ã³¸®±â ÄÚµå¸¦ Ãß°¡ ¹×/¶Ç´Â ±âº»°ªÀ» È£ÃâÇÕ´Ï´Ù.
	CGraphicEditorDoc* pDoc = GetDocument();

	if (ldown){
		if (m_changeSize == TRUE){
			switch (m_changeSizePosition){
			case 0:{ // ¿ŞÂÊ À§
				pDoc->vo[m_currentSelected]->setStartX(point.x);
				pDoc->vo[m_currentSelected]->setStartY(point.y);
				break;
			}
			case 1:{ // ¿À¸¥ÂÊ À§
				pDoc->vo[m_currentSelected]->setEndX(point.x);
				pDoc->vo[m_currentSelected]->setStartY(point.y);
				break;
			}
			case 2:{ // ¿ŞÂÊ ¾Æ·¡
				pDoc->vo[m_currentSelected]->setStartX(point.x);
				pDoc->vo[m_currentSelected]->setEndY(point.y);
				break;
			}
			case 3:{ // ¿À¸¥ÂÊ ¾Æ·¡
				pDoc->vo[m_currentSelected]->setEndX(point.x);
				pDoc->vo[m_currentSelected]->setEndY(point.y);
				break;
			}
			default:{
				break;
			}
			}
			Invalidate();
			return;
		}
		switch (CurrentMode)
		{
		case DrawMode::LINE:{
			pDoc->m_line->SetEnd(point);
			Invalidate();
			break;
		}
		case DrawMode::ELLP:{
			pDoc->m_ellp->SetEnd(point);

			Invalidate();
			break;
		}


		case DrawMode::RECT:{
			pDoc->m_rect->setEndX(point.x);
			pDoc->m_rect->setEndY(point.y);
			Invalidate();
		}
		default:{
			if (m_move == TRUE){ // °´Ã¼°¡ ¼±ÅÃµÇ¾úÀ» ¶§ µµÇüÀ» Àâ°í ¿òÁ÷ÀÌ´Â »óÈ²
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
	// TODO: ¿©±â¿¡ ¸í·É Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	if (CurrentMode != DrawMode::LINE)
	CurrentMode = DrawMode::LINE;
	else
		CurrentMode = DrawMode::NOTHING;
}


void CGraphicEditorView::OnPolyline()
{
	// TODO: ¿©±â¿¡ ¸í·É Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	if (CurrentMode != DrawMode::POLY)
	CurrentMode = DrawMode::POLY;
	else
		CurrentMode = DrawMode::NOTHING;
}


void CGraphicEditorView::OnRectangle()
{
	// TODO: ¿©±â¿¡ ¸í·É Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	if (CurrentMode != DrawMode::RECT)
	CurrentMode = DrawMode::RECT;
	else
		CurrentMode = DrawMode::NOTHING;
}


void CGraphicEditorView::OnEllipse()
{
	// TODO: ¿©±â¿¡ ¸í·É Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	if (CurrentMode != DrawMode::ELLP)
	CurrentMode = DrawMode::ELLP;
	else
		CurrentMode = DrawMode::NOTHING;
}


void CGraphicEditorView::OnText()
{
	// TODO: ¿©±â¿¡ ¸í·É Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	if (CurrentMode != DrawMode::TEXT)
	CurrentMode = DrawMode::TEXT;
	else
		CurrentMode = DrawMode::NOTHING;
}



void CGraphicEditorView::OnUpdateText(CCmdUI *pCmdUI)
{
	// TODO: ¿©±â¿¡ ¸í·É ¾÷µ¥ÀÌÆ® UI Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	pCmdUI->SetCheck(CurrentMode == DrawMode::TEXT);
}


void CGraphicEditorView::OnUpdateRectangle(CCmdUI *pCmdUI)
{
	// TODO: ¿©±â¿¡ ¸í·É ¾÷µ¥ÀÌÆ® UI Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	pCmdUI->SetCheck(CurrentMode == DrawMode::RECT);
}


void CGraphicEditorView::OnUpdatePolyline(CCmdUI *pCmdUI)
{
	// TODO: ¿©±â¿¡ ¸í·É ¾÷µ¥ÀÌÆ® UI Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	pCmdUI->SetCheck(CurrentMode == DrawMode::POLY);
}


void CGraphicEditorView::OnUpdateEllipse(CCmdUI *pCmdUI)
{
	// TODO: ¿©±â¿¡ ¸í·É ¾÷µ¥ÀÌÆ® UI Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	pCmdUI->SetCheck(CurrentMode == DrawMode::ELLP);
}


void CGraphicEditorView::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO: ¿©±â¿¡ ¸í·É ¾÷µ¥ÀÌÆ® UI Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	pCmdUI->SetCheck(CurrentMode == DrawMode::LINE);
}


void CGraphicEditorView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ¿©±â¿¡ ¸Ş½ÃÁö Ã³¸®±â ÄÚµå¸¦ Ãß°¡ ¹×/¶Ç´Â ±âº»°ªÀ» È£ÃâÇÕ´Ï´Ù.
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

	for (auto i : pDoc->vo) i->draw(pDC); // ÀúÀåµÈ ¸ğµç µµÇü °´Ã¼ Ãâ·Â
	
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
		//pDoc->m_poly.draw(pDC);
		break;
	}
	default:
		break;
	}
	// TODO: ¿©±â¿¡ Æ¯¼öÈ­µÈ ÄÚµå¸¦ Ãß°¡ ¹×/¶Ç´Â ±âº» Å¬·¡½º¸¦ È£ÃâÇÕ´Ï´Ù.
}



void CGraphicEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: ¿©±â¿¡ ¸Ş½ÃÁö Ã³¸®±â ÄÚµå¸¦ Ãß°¡ ¹×/¶Ç´Â ±âº»°ªÀ» È£ÃâÇÕ´Ï´Ù.

	CGraphicEditorDoc* pDoc = GetDocument();

	//pDoc->m_polypoints.Add(NULL);

	CFormView::OnLButtonDblClk(nFlags, point);
}


void CGraphicEditorView::OnEditUndo()
{
	// TODO: ¿©±â¿¡ ¸í·É Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	CGraphicEditorDoc* pDoc = GetDocument();
	Invalidate();
	pDoc->vo.pop_back();
	Invalidate();
}
<<<<<<< HEAD
=======


void CGraphicEditorView::OnBnClickedLinecolor() // ¼± »ö ¼³Á¤À» ºÒ·¯¿È
{
	CColorDialog cdlg;
	CGraphicEditorDoc* pDoc = GetDocument();

	if (cdlg.DoModal() == IDOK)
	{
		switch (CurrentMode){
		case DrawMode::LINE:{
			pDoc->m_line->setLineColor(cdlg.GetColor());

			break;
		}
		case DrawMode::RECT:{
			pDoc->m_rect->setLineColor(cdlg.GetColor());

			break;
		}

		case DrawMode::POLY:{
			pDoc->m_poly->setLineColor(cdlg.GetColor());
			break;
		}
		}
	}
	//½Ã¹ß
	// TODO: ¿©±â¿¡ ÄÁÆ®·Ñ ¾Ë¸² Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
}


void CGraphicEditorView::OnBnClickedPanecolor()
{
	CColorDialog cdlg;

	if (cdlg.DoModal() == IDOK)
	{

	}

	// TODO: ¿©±â¿¡ ÄÁÆ®·Ñ ¾Ë¸² Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
}
>>>>>>> origin/?´ì›ì¤€2
