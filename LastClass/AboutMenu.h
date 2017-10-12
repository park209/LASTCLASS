//AboutMenu.h
#ifndef _ABOUTMENU_H
#define _ABOUTMENU_H

#include <afxwin.h>
typedef signed long int Long;

class ClassDiagramForm;
class AboutMenu : public CFrameWnd {
public:
	AboutMenu();
private:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
private:
};
#endif // !_ABOUTMENU_H
