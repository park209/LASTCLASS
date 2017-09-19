//DownArrowKey.cpp

#include "DownArrowKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Character.h"

DownArrowKey::DownArrowKey() {
}

DownArrowKey::DownArrowKey(const DownArrowKey& source) {
}

DownArrowKey::~DownArrowKey() {
}

void DownArrowKey::KeyPress(TextEdit *textEdit) {
	CPaintDC dc(textEdit);

	CFont cFont;
	cFont.CreateFont(textEdit->GetRowHeight(), 0, 0, 0, FW_LIGHT, FALSE, FALSE, 0, DEFAULT_CHARSET,      // 글꼴 설정
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "돋움체");
	textEdit->SetFont(&cFont, TRUE);
	CFont *oldFont = dc.SelectObject(&cFont); // 폰트 시작


	Long x = textEdit->caret->GetCurrentCaretX();
	Long y = textEdit->caret->GetCurrentCaretY();

	Long rowIndex = y + textEdit->GetRowHeight();

	textEdit->caret->MoveToPoint(textEdit, &dc, CPoint(x, rowIndex));

	//Long rowDownWidth = 0;   //아래줄길이
	//Long rowCurrentWidth = 0;   //현재줄길이
	//Long i = 0;
	//while (i < textEdit->characterIndex) { // 현재줄에서 캐릭터인덱스까지 너비 구한다
	//	rowCurrentWidth += dc.GetTextExtent(textEdit->text->GetAt(textEdit->rowIndex)->GetAt(i)->MakeCString()).cx;
	//	i++;
	//}
	//if (textEdit->rowIndex < textEdit->text->GetLength() - 1) { // 0 일수 없으니까
	//	textEdit->rowIndex++;
	//	textEdit->characterIndex = 0; // 아래줄에서 캐릭터인덱스 구한다(너비로)
	//	while (rowDownWidth < rowCurrentWidth && textEdit->characterIndex < textEdit->text->GetAt(textEdit->rowIndex)->GetLength()) {
	//		rowDownWidth += dc.GetTextExtent(textEdit->text->GetAt(textEdit->rowIndex)->GetAt(textEdit->characterIndex)->MakeCString()).cx;
	//		textEdit->characterIndex++; // 한개 오바됨
	//	}
	//	if (rowCurrentWidth < rowDownWidth && textEdit->characterIndex > 0 &&
	//		rowCurrentWidth <= rowDownWidth - dc.GetTextExtent(textEdit->text->GetAt(textEdit->rowIndex)->GetAt(textEdit->characterIndex - 1)->MakeCString()).cx / 2) {
	//		textEdit->characterIndex--;
	//	}
	//}
	//else {
	//	textEdit->rowIndex = textEdit->text->GetLength() - 1;
	//}
	dc.SelectObject(oldFont);
	cFont.DeleteObject(); // 폰트
}