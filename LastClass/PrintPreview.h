//PrintPreview.h
#ifndef _PRINTPREVIEW_H
#define _PRINTPREVIEW_H

#include <afxwin.h>
typedef signed long int Long;

class ClassDiagramForm;
class PrintPreview : public CWnd {
public:
	PrintPreview(ClassDiagramForm *classDiagramForm);
private:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNextButton();
	afx_msg void OnPriviousButton();
	afx_msg void OnPrintButton();
	DECLARE_MESSAGE_MAP()
private:
	ClassDiagramForm *classDiagramForm;
	CButton *nextButton;
	CButton *priviousButton;
	CButton *printButton;
	Long horizontalPage;
	Long verticalPage;
};
#endif // !_PRINTPREVIEW_H
