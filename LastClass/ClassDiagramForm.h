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
	ClassDiagramForm();
public:
	Long Save();
	Long Load();
	Long TextSave();
	Long TextLoad();
public:
	Long GetRowIndex() const;
	Long GetCharacterIndex() const;
private:
	Long startX;
	Long startY;
	Long currentX;
	Long currentY;
	Long rowIndex;
	Long characterIndex;
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

inline Long ClassDiagramForm::GetRowIndex() const {
	return this->rowIndex;
}
inline Long ClassDiagramForm::GetCharacterIndex() const {
	return this->characterIndex;
}

#endif // _CLASSDIAGRAM_H
