
// LeftView.h : CLeftView 클래스의 인터페이스
//


#pragma once

class CGraphicEditorDoc;

class CLeftView : public CTreeView
{
protected: // serialization에서만 만들어집니다.
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// 특성입니다.
public:
	CGraphicEditorDoc* GetDocument();

// 작업입니다.
public:

// 재정의입니다.
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // LeftView.cpp의 디버그 버전
inline CGraphicEditorDoc* CLeftView::GetDocument()
   { return reinterpret_cast<CGraphicEditorDoc*>(m_pDocument); }
#endif

