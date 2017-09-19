//TextEdit.h

#ifndef _TEXTEDIT_H
#define _TEXTEDIT_H

#include <afxwin.h>
#include <imm.h>
#include <string>

typedef signed long int Long;

class Text;
class Figure;
class Caret;
class KeyBoard;
class TextEdit : public CFrameWnd {
public:
	TextEdit(Figure *figure);
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg Long OnComposition(WPARAM wParam, LPARAM lParam);
	afx_msg void OnKillFocus(CWnd *pNewWnd);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDoubleClicked(UINT nFlags, CPoint point);

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnIMENotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	Long GetFlagInsert() const;

	Figure* GetFigure() const;
	Long GetRowHeight() const;
	Long GetKoreanEnglish() const;
	Long GetFlagBuffer() const;
public:
	Text *text;
	Caret *caret;
	KeyBoard *keyBoard;
	Long flagInsert;//flag
private:
	Figure *figure;
	Long rowHeight;//figure에서 저장을 해줘야 하기때문에 삭제가능
	Long koreanEnglish;//flag
	Long flagBuffer;//flag
	Long selectedX;//보류
	Long selectedY;//보류
};

inline Long TextEdit::GetFlagInsert() const {
	return this->flagInsert;
}

inline Figure* TextEdit::GetFigure() const {
	return const_cast<Figure*>(this->figure);
}
inline Long TextEdit::GetRowHeight() const {
	return this->rowHeight;
}
inline Long TextEdit::GetKoreanEnglish() const {
	return this->koreanEnglish;
}
inline Long TextEdit::GetFlagBuffer() const {
	return this->flagBuffer;
}

#endif // _TEXTEDIT_H