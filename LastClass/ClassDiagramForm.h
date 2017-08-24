#ifndef _CLASSDIAGRAM_H
#define _CLASSDIAGRAM_H

#include <afxwin.h>

class Diagram;
class ClassDiagramForm : public CFrameWnd {
public:
	Diagram *diagram;
public:
	ClassDiagramForm();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif // _CLASSDIAGRAM_H
