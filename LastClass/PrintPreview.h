//PrintPreview.h
#ifndef _PRINTPREVIEW_H
#define _PRINTPREVIEW_H

#include <afxwin.h>
#include <afxpriv.h>
typedef signed long int Long;

class LastClass;
class PrintPreview : public CWnd {
public:
	PrintPreview(LastClass *lastClass);
	void OnPrint(CDC *cdc , CPrintInfo *pInfo, UINT page);
	void OnEndPrinting(CDC *pDc, CPrintInfo *pInfo);
	void OnBeginPrinting(CDC *pDc, CPrintInfo *pInfo);
private:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnDraw(CDC *cdc ) ;
	afx_msg void OnClose();
	afx_msg void OnNextButton();
	afx_msg void OnpreviousButton();
	afx_msg void OnPrintButton();
	DECLARE_MESSAGE_MAP()
protected:
	virtual void OnFilePrintPreview();
	 virtual BOOL OnPreparePrinting(CPrintInfo *pInfo);
private:
	LastClass *lastClass;
	CButton *nextButton;
	CButton *previousButton;
	CButton *printButton;
	Long horizontalPage;
	Long verticalPage;
};
#endif // !_PRINTPREVIEW_H
