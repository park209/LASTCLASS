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
	Long GetSelectedX() const;
	Long GetSelectedY() const;

	Figure* GetFigure() const;
	Long GetRowHeight() const;
	Long GetKoreanEnglish() const;
	Long GetFlagBuffer() const;
	CString GetCopyBuffer() const;
public:
	Text *text;
	Caret *caret;
	KeyBoard *keyBoard;
	Long flagInsert; //flag
	Long flagSelection;
	Long rowHeight; //figure���� ������ ����� �ϱ⶧���� ��������
	Long selectedX; //����
	Long selectedY; //����
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
inline Long TextEdit::GetSelectedY() const {
	return this->selectedY;
}

#endif // _TEXTEDIT_H