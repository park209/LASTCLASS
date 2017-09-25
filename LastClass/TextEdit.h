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
class HistoryText;
class TextAreaSelected;
class TextEdit : public CWnd { // CWnd 상속으로 바꿔야함
public:
	TextEdit(Figure *figure);
	afx_msg void OnClose();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg Long OnComposition(WPARAM wParam, LPARAM lParam);
	afx_msg void OnKillFocus(CWnd *pNewWnd);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnIMENotify(WPARAM wParam, LPARAM lParam);
	//afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	Long GetFlagInsert() const;
	Long GetSelectedX() const;
	Long GetSelectedCharacterIndex() const;
	Long GetSelectedRowIndex() const;

	Figure* GetFigure() const;
	Long GetRowHeight() const;
	Long GetKoreanEnglish() const;
	Long GetFlagBuffer() const;
	CString GetCopyBuffer() const;
	Long GetCurrentX() const;
public:
	Text *text;
	Caret *caret;
	KeyBoard *keyBoard;
	HistoryText *historyText;
	TextAreaSelected *textAreaSelected;
	Long flagInsert; //flag
	Long flagSelection;
	Long rowHeight; //figure에서 저장을 해줘야 하기때문에 삭제가능
	Long selectedX; //보류
	Long selectedCharacterIndex;
	Long selectedRowIndex; //보류
	CString copyBuffer;
private:
	Figure *figure;
	Long koreanEnglish; //flag
	Long flagBuffer; //flag
	Long currentX;
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
inline CString TextEdit::GetCopyBuffer() const {
	return this->copyBuffer;
}
inline Long TextEdit::GetSelectedX() const {
	return this->selectedX;
}
inline Long TextEdit::GetSelectedCharacterIndex() const {
	return this->selectedCharacterIndex;
}
inline Long TextEdit::GetSelectedRowIndex() const {
	return this->selectedRowIndex;
}
inline Long TextEdit::GetCurrentX() const {
	return this->currentX;
}

#endif // _TEXTEDIT_H