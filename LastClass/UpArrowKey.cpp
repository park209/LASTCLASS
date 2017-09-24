//UpArrowKey.cpp

#include "UpArrowKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Character.h"

UpArrowKey::UpArrowKey() {
}

UpArrowKey::UpArrowKey(const UpArrowKey& source) {
}

UpArrowKey::~UpArrowKey() {
}

void UpArrowKey::KeyPress(TextEdit *textEdit) {
	CPaintDC dc(textEdit);
	if (GetKeyState(VK_SHIFT) >= 0) {
		if (textEdit->flagSelection == 1) {
			textEdit->flagSelection = 0;
		}
	}
	else {
		if (textEdit->flagSelection == 0) {
			textEdit->flagSelection = 1;
			textEdit->selectedX = textEdit->caret->GetCurrentCaretX();
			textEdit->selectedRowIndex = textEdit->caret->GetRowIndex();
			//textEdit->selectedX = textEdit->caret->GetCharacterIndex(); // 좌표로 바꿈
			//textEdit->selectedY = textEdit->caret->GetRowIndex();
		}
	}
	CFont cFont;
	cFont.CreateFont(textEdit->rowHeight, 0, 0, 0, FW_LIGHT, FALSE, FALSE, 0, DEFAULT_CHARSET,// 글꼴 설정
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "굴림체");
	textEdit->SetFont(&cFont, TRUE);
	/*CFont *cFont = dc.GetCurrentFont();
	textEdit->SetFont(cFont, TRUE);*/
	CFont *oldFont = dc.SelectObject(&cFont); // 폰트 시작

	Long x = textEdit->caret->GetCurrentCaretX();
	Long y = textEdit->caret->GetRowIndex();

	Long rowIndex = y - textEdit->GetRowHeight();

	textEdit->caret->MoveToPoint(textEdit, &dc, CPoint(x, rowIndex));

	dc.SelectObject(oldFont);
	cFont.DeleteObject(); // 폰트
}