#pragma once


// SelectAble

class SelectAble : public CPaneDialog
{
	DECLARE_DYNAMIC(SelectAble)

public:
	SelectAble();
	virtual ~SelectAble();

	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
	{
		CPaneDialog::OnUpdateCmdUI(pTarget, FALSE);
	}

protected:
	DECLARE_MESSAGE_MAP()
};


