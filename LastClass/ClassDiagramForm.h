//ClassDiagramForm.h

#ifndef _CLASSDIAGRAM_H
#define _CLASSDIAGRAM_H

#include <afxwin.h>

typedef signed long int Long;

enum gab { GabX = 6, GabY = 2, MemoGab = 20 };

class Diagram; //전방선언
class Text;
class TextEdit;
class Selection;
class MouseLButton;
class KeyBoard;
class ClassDiagramForm : public CFrameWnd { //CFrameWnd 에 상속관계 표기
public:
	Diagram *diagram;
	Text *text;
	TextEdit *textEdit;
	Selection *selection;
	MouseLButton *mouseLButton;
	KeyBoard *keyBoard;
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