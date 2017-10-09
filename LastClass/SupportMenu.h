//SupportMenu.h
#ifndef _SUPPORTMENU_H
#define _SUPPORTMENU_H

#include <afxwin.h>
typedef signed long int Long;

class ClassDiagramForm;
class SupportMenu : public CWnd {
public:
	SupportMenu();
private:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnNextButton();
	afx_msg void OnPriviousButton();
	DECLARE_MESSAGE_MAP()
private:
	CButton *nextButton;
	CButton *priviousButton;
};
#endif // !_SUPPORTMENU_H
