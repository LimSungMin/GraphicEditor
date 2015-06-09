
// GraphicEditorView.h : CGraphicEditorView 클래스의 인터페이스
//

#pragma once

#include "resource.h"


class CGraphicEditorView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CGraphicEditorView();
	DECLARE_DYNCREATE(CGraphicEditorView)

public:
	enum{ IDD = IDD_GRAPHICEDITOR_FORM };

// 특성입니다.
public:
	CGraphicEditorDoc* GetDocument() const;
	enum DrawMode
	{
		NOTHING = -1, LINE, POLY, RECT, ELLP, TEXT
	};
	int CurrentMode;
	

	POINT pos;
	POINT postPos;
	BOOL ldown;
	BOOL m_move = FALSE; // 도형을 잡고 끄는 상태
	BOOL m_changeSize = FALSE; // 도형 끄트머리를 잡고 크기를 변경하는 상태
	BOOL m_textin = FALSE;
	BOOL m_firstclick = TRUE;
	CArray<TCHAR, TCHAR> m_str;
	int m_changeSizePosition = -1;
	int m_currentSelected; // 선택된 도형의 m_shape index
	POINT m_clickedPoint; // 도형을 선택했을 때 클릭된 마우스 포인터의 좌표
	GGroup m_group;

	int m_fontnumb;

	int polypointindex; // 선택된 사각형 임시 저장 좌표
	int m_lineSize;		// MainFrm 으로부터 선 두께를 가져옵니다.
	int m_linePattern;	// MainFrm 으로부터 선 패턴을 가져옵니다.
	int m_fillPattern;	// MainFrm 으로부터 내부 패턴을 가져옵니다.
	BOOL polypointmove = FALSE;

// 작업입니다.
public:
	int getLineSize();
	int getLinePattern();
	int getFillPattern();
	int getFont();
// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CGraphicEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLine();
	afx_msg void OnPolyline();
	afx_msg void OnRectangle();
	afx_msg void OnEllipse();
	afx_msg void OnText();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnUpdateText(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRectangle(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePolyline(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEllipse(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLine(CCmdUI *pCmdUI);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	CString m_stringreg;
	virtual void OnDraw(CDC* /*pDC*/);
//	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEditUndo();
	afx_msg void OnBnClickedLinecolor();
	afx_msg void OnBnClickedPanecolor();
	afx_msg void OnDelete();
	afx_msg void OnSelect();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnGroup();
	afx_msg void OnGroupdeselect();
	afx_msg void OnCbnSelchangeLinethick();
	afx_msg void OnCbnSelchangeLinepattern();
	afx_msg void OnCbnSelchangeFillpattern();
	afx_msg void OnCut();
	afx_msg void OnPaste();
	afx_msg void OnBnClickedFontcolor();
};

#ifndef _DEBUG  // GraphicEditorView.cpp의 디버그 버전
inline CGraphicEditorDoc* CGraphicEditorView::GetDocument() const
   { return reinterpret_cast<CGraphicEditorDoc*>(m_pDocument); }
#endif

