//TextEdit.h

#ifndef _TEXTEDIT_H
#define _TEXTEDIT_H

#include <afxwin.h>
#include "ClassDiagramForm.h"
#include "Text.h"

typedef signed long int Long;

//전방선언
class TextEdit : public CFrameWnd { //CFrameWnd 에 상속관계 표기
public:
	TextEdit(ClassDiagramForm *classDiagramForm, Long x, Long y, Long width, Long height); // 이건 생성자????
public:
	//Long Save();
	//Long Load();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	Long GetX() const;
	Long GetY() const;
	Long GetWidth() const;
	Long GetHeight() const;
private:
	ClassDiagramForm *classDiagramForm;
	Long x;
	Long y;
	Long width;
	Long height;
};

inline Long TextEdit::GetX() const {
	return this->x;
}
inline Long TextEdit::GetY() const {
	return this->y;
}
inline Long TextEdit::GetWidth() const {
	return this->width;
}
inline Long TextEdit::GetHeight() const {
	return this->height;
}

#endif // _TEXTEDIT_H