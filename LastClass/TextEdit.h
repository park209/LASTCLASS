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
	Long GetRowIndex() const;
	Long GetCharacterIndex() const;
	Long GetFlagInsert() const;

	Figure* GetFigure() const;
	Long GetStartX() const;
	Long GetStartY() const;
	Long GetCurrentX() const;
	Long GetCurrentY() const;
	Long GetRowHeight() const;
	Long GetKoreanEnglish() const;
	Long GetFlagBuffer() const;
public:
	Text *text;
	Caret *caret;
	KeyBoard *keyBoard;
	Long rowIndex;
	Long characterIndex;
	Long flagInsert;
private:
	Figure *figure;
	Long startX;
	Long startY;
	Long currentX;
	Long currentY;
	Long rowHeight;
	Long koreanEnglish;
	Long flagBuffer;
};

inline Long TextEdit::GetRowIndex() const {
	return this->rowIndex;
}
inline Long TextEdit::GetCharacterIndex() const {
	return this->characterIndex;
}
inline Long TextEdit::GetFlagInsert() const {
	return this->flagInsert;
}

inline Figure* TextEdit::GetFigure() const {
	return const_cast<Figure*>(this->figure);
}
inline Long TextEdit::GetStartX() const {
	return this->startX;
}
inline Long TextEdit::GetStartY() const {
	return this->startY;
}
inline Long TextEdit::GetCurrentX() const {
	return this->currentX;
}
inline Long TextEdit::GetCurrentY() const {
	return this->currentY;
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