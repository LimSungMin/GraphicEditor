#pragma once


// BottonAble

class BottonAble : public CPaneDialog
{
	DECLARE_DYNAMIC(BottonAble)

public:
	BottonAble();
	virtual ~BottonAble();

	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
	{
		CPaneDialog::OnUpdateCmdUI(pTarget, FALSE);
	}

protected:
	DECLARE_MESSAGE_MAP()
};


