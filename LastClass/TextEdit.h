//TextEdit.h

#ifndef _TEXTEDIT_H
#define _TEXTEDIT_H

#include <afxwin.h>
#include <imm.h>
#include "ClassDiagramForm.h"

typedef signed long int Long;

class TextEdit : public CFrameWnd {
public:
	TextEdit(ClassDiagramForm *classDiagramForm, Long x, Long y, Long width, Long height);
public:
	//Long Save();
	//Long Load();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd *pNewWnd);
	afx_msg Long OnComposition(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnIMENotify(WPARAM wParam,LPARAM lParam);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	Long GetX() const;
	Long GetY() const;
	Long GetWidth() const;
	Long GetHeight() const;
	Long GetRowIndex() const;
	Long GetCharacterIndex() const;
	Long GetKoreanEnglish() const;
private:
	ClassDiagramForm *classDiagramForm;
	Long x;
	Long y;
	Long width;
	Long height;
	Long rowIndex;
	Long characterIndex;
	Long koreanEnglish;
	Long flagBuffer;
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
inline Long TextEdit::GetRowIndex() const {
	return this->rowIndex;
}
inline Long TextEdit::GetCharacterIndex() const {
	return this->characterIndex;
}
inline Long TextEdit::GetKoreanEnglish() const {
	return this->koreanEnglish;
}

#endif // _TEXTEDIT_H