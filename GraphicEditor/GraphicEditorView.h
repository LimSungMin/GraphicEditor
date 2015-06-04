
// GraphicEditorView.h : CGraphicEditorView 클래스의 인터페이스
//

#pragma once

#include "resource.h"
#include "Line.h"


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
		LINE, POLY, RECT, ELLP, TEXT
	};
	int CurrentMode;
	Line line;
	POINT pos;
	POINT postPos;
	BOOL ldown;
	BOOL m_textin = FALSE;
	
	CArray<TCHAR, TCHAR> m_str;
	
// 작업입니다.
public:

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
};

#ifndef _DEBUG  // GraphicEditorView.cpp의 디버그 버전
inline CGraphicEditorDoc* CGraphicEditorView::GetDocument() const
   { return reinterpret_cast<CGraphicEditorDoc*>(m_pDocument); }
#endif

