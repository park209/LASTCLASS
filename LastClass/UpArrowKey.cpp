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

	CFont cFont;
	cFont.CreateFont(textEdit->GetRowHeight(), 0, 0, 0, FW_LIGHT, FALSE, FALSE, 0, DEFAULT_CHARSET,      // 글꼴 설정
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "돋움체");
	textEdit->SetFont(&cFont, TRUE);
	CFont *oldFont = dc.SelectObject(&cFont); // 폰트 시작
	
	Long x = textEdit->caret->GetCurrentCaretX();
	Long y = textEdit->caret->GetCurrentCaretY();

	Long rowIndex = y-textEdit->GetRowHeight();

	textEdit->caret->MoveToPoint(textEdit, &dc, CPoint(x, rowIndex));

	dc.SelectObject(oldFont);
	cFont.DeleteObject(); // 폰트



	//while (i < textEdit->caret->GetCharacterIndex()) { // 현재줄에서 캐릭터인덱스까지 너비 구한다
	//	rowCurrentWidth += dc.GetTextExtent(textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetAt(i)->MakeCString()).cx;
	//	i++;
	//}
	//if (textEdit->caret->GetRowIndex() > 0) {
	//	textEdit->caret->GetRowIndex();
	//	textEdit->caret->GetCharacterIndex(); = 0; // 윗줄에서 캐릭터인덱스 구한다(너비로)
	//	while (rowUpWidth < rowCurrentWidth && textEdit->caret->GetCharacterIndex() < textEdit->text->GetAt(textEdit->rowIndex)->GetLength()) {
	//		rowUpWidth += dc.GetTextExtent(textEdit->text->GetAt(textEdit->rowIndex)->GetAt(textEdit->caret->GetCharacterIndex();)->MakeCString()).cx;
	//		textEdit->caret->MoveForwardCharacterIndex(); // 한개 오바됨
	//	}
	//	if (rowCurrentWidth < rowUpWidth && textEdit->caret->GetCharacterIndex(); > 0 &&
	//		rowCurrentWidth <= rowUpWidth - dc.GetTextExtent(textEdit->text->GetAt(textEdit->rowIndex)->GetAt(textEdit->caret->GetCharacterIndex(); - 1)->MakeCString()).cx / 2) {
	//			
	//	}
	//}
	//else {
	//	textEdit->rowIndex = 0;
	//}

}