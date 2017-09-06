//ClassDiagramForm.h

#ifndef _CLASSDIAGRAM_H
#define _CLASSDIAGRAM_H

#include <afxwin.h>

typedef signed long int Long;

class Diagram; //전방선언
class Text;
class ClassDiagramForm : public CFrameWnd { //CFrameWnd 에 상속관계 표기
public:
	Diagram *diagram;
	Text *text;
public:
	ClassDiagramForm(); // 이건 생성자????
public:
	Long Save();
	Long Load();
private:
	Long startX;
	Long startY;
	Long currentX;
	Long currentY;
	Long rowIndex;
	Long characterIndex;
	Long selected;
	bool classButton;	//임시버튼
	bool relationButton;	//임시버튼
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif // _CLASSDIAGRAM_H
