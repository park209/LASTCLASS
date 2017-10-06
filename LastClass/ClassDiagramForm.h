//ClassDiagramForm.h

#ifndef _CLASSDIAGRAM_H
#define _CLASSDIAGRAM_H

#include <afxwin.h>

typedef signed long int Long;

enum gab { GabX = 8, GabY = 2, MemoGab = 20, CaretWidth = 2};

class Diagram; //전방선언
class TextEdit;
class Selection;
class MouseLButton;
class Scroll;
class KeyBoard;
class HistoryGraphic;
class ClassDiagramForm : public CFrameWnd { //CFrameWnd 에 상속관계 표기
public:
	Diagram *diagram;
	TextEdit *textEdit;
	Selection *selection;
	MouseLButton *mouseLButton;
	KeyBoard *keyBoard;
	Scroll *verticalScrollBar;
	Scroll *horizontalScroll;
	HistoryGraphic *historyGraphic;
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
	bool isDblclk;
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar); 
	afx_msg BOOL OnMouseWheel(UINT nFlags,	short zDelta,CPoint pt);
	DECLARE_MESSAGE_MAP()
};
#endif // _CLASSDIAGRAM_H