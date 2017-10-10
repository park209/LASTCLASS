#ifndef _PRINTPREVIEWSTATE_H
#define _PRINTPREVIEWSTATE_H

#include <afxwin.h>
#include <afxpriv.h>

class PrintPreviewState : public CPreviewView {
public:
	PrintPreviewState();
private:
	afx_msg void OnInitialUpdate();
	afx_msg void OnDraw(CDC* pDC);
private:
	CRectTracker m_tracker;
};
	
#endif // !_PRINTPREVIEWSTATE_H

