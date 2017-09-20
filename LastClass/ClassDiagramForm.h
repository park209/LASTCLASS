//ClassDiagramForm.h

#ifndef _CLASSDIAGRAM_H
#define _CLASSDIAGRAM_H

#include <afxwin.h>

typedef signed long int Long;

class Diagram; //���漱��
class Text;
class TextEdit;
class Selection;
class DrawingController;
class ClassDiagramForm : public CFrameWnd { //CFrameWnd �� ��Ӱ��� ǥ��
public:
	Diagram *diagram;
	Text *text;
	TextEdit *textEdit;
	Selection *selection;
	DrawingController *drawingController;
public:
	ClassDiagramForm();
public:
	Long Load();
	Long Save();
private:
	Long startX;
	Long startY;
	Long currentX;
	Long currentY;
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};
#endif // _CLASSDIAGRAM_H