//LastClass.h

#ifndef _LASTCLASS_H
#define _LASTCLASS_H

#include <afxwin.h>
using namespace std;

typedef signed long int Long;

class StatusBar;
class ToolBar;
class Menu;
class ClassDiagramForm;
class ToolBar;
class StatusBar;
class PrintPreview;
class LastClass : public CFrameWnd {
public:
	LastClass();
public:
	ClassDiagramForm *classDiagramForm;
	Menu *menu;
	ToolBar *toolBar;
	StatusBar *statusBar;
	PrintPreview *printPreview;
	Long one = 0;
public:
	afx_msg void OnClose();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd *pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMyMenu(UINT parm_control_id);
	afx_msg void OnMyToolBar(UINT parm_control_id);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	DECLARE_MESSAGE_MAP()
};

#endif // _LASTCLASS_H