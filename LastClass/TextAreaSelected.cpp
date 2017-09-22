//TextAreaSelected.cpp

#include "TextAreaSelected.h"
#include "TextEdit.h"
#include "Caret.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"

TextAreaSelected::TextAreaSelected() {
}

TextAreaSelected::TextAreaSelected(const TextAreaSelected& source) {
}

TextAreaSelected::~TextAreaSelected() {
}

void TextAreaSelected::SelectTextArea(TextEdit *textEdit, CPaintDC *dc) {
	CRect rect;
	this->startCharacterIndex = 0;
	this->startRowIndex = 0;
	this->endCharacterIndex = 0;
	this->endRowIndex = 0;
	Long i;
	Long x;
	Long width = 0;

	CString cString1;
	if (textEdit->selectedY == textEdit->caret->GetRowIndex()) {
		if (textEdit->selectedX < textEdit->caret->GetCharacterIndex()) {
			this->startCharacterIndex = textEdit->selectedX;
			this->startRowIndex = textEdit->selectedY;
			this->endCharacterIndex = textEdit->caret->GetCharacterIndex();
			this->endRowIndex = textEdit->caret->GetRowIndex();
		}
		else {
			this->startCharacterIndex = textEdit->caret->GetCharacterIndex();
			this->startRowIndex = textEdit->caret->GetRowIndex();
			this->endCharacterIndex = textEdit->selectedX;
			this->endRowIndex = textEdit->selectedY;
		}
		width = 0;
		i = startCharacterIndex;
		while (i < endCharacterIndex) { // 첫줄
			cString1 += textEdit->text->GetAt(this->startRowIndex)->GetAt(i)->MakeCString();
			width += dc->GetTextExtent(textEdit->text->GetAt(this->startRowIndex)->GetAt(i)->MakeCString()).cx;
			i++;
		}
		x = 5;
		i = 0;
		while (i < startCharacterIndex) { // 현재줄에서 캐릭터인덱스까지 너비 구한다
			x += dc->GetTextExtent(textEdit->text->GetAt(this->startRowIndex)->GetAt(i)->MakeCString()).cx;
			i++;
		}
		rect = { x, this->startRowIndex * textEdit->rowHeight + 5, x + width, this->startRowIndex * textEdit->rowHeight + textEdit->rowHeight + 5 };
		dc->DrawText(cString1, rect, DT_EDITCONTROL | DT_EXPANDTABS);

		textEdit->copyBuffer = cString1;
	}
	else {
		if (textEdit->selectedY < textEdit->caret->GetRowIndex()) {
			this->startCharacterIndex = textEdit->selectedX;
			this->startRowIndex = textEdit->selectedY;
			this->endCharacterIndex = textEdit->caret->GetCharacterIndex();
			this->endRowIndex = textEdit->caret->GetRowIndex();
		}
		else {
			this->startCharacterIndex = textEdit->caret->GetCharacterIndex();
			this->startRowIndex = textEdit->caret->GetRowIndex();
			this->endCharacterIndex = textEdit->selectedX;
			this->endRowIndex = textEdit->selectedY;
		}
		width = 0;
		i = startCharacterIndex;
		while (i < textEdit->text->GetAt(this->startRowIndex)->GetLength()) { // 첫줄
			cString1 += textEdit->text->GetAt(this->startRowIndex)->GetAt(i)->MakeCString();
			width += dc->GetTextExtent(textEdit->text->GetAt(this->startRowIndex)->GetAt(i)->MakeCString()).cx;
			i++;
		}
		cString1 += "\r\n";
		x = 5;
		i = 0;
		while (i < startCharacterIndex) { // 현재줄에서 캐릭터인덱스까지 너비 구한다
			x += dc->GetTextExtent(textEdit->text->GetAt(this->startRowIndex)->GetAt(i)->MakeCString()).cx;
			i++;
		}
		rect = { x, this->startRowIndex * textEdit->rowHeight + 5, x + width, this->startRowIndex * textEdit->rowHeight + textEdit->rowHeight + 5 };
		dc->DrawText(cString1, rect, DT_EDITCONTROL | DT_EXPANDTABS);

		string string2; // 중간
		if (this->startRowIndex + 1 < endRowIndex) {
			i = this->startRowIndex + 1;
			while (i < this->endRowIndex) {
				string2 += textEdit->text->GetAt(i)->PrintRowString().c_str();
				string2 += "\r\n";
				i++;
			}
			x = 5;
			rect = { x, (this->startRowIndex + 1) * textEdit->rowHeight + 5, 1000, (this->endRowIndex - 1) * textEdit->rowHeight + textEdit->rowHeight + 5 };
			dc->DrawText(string2.c_str(), rect, DT_EDITCONTROL | DT_EXPANDTABS);
		}

		CString cString3;
		width = 0;
		i = 0;
		while (i < this->endCharacterIndex) { // 첫줄
			cString3 += textEdit->text->GetAt(this->endRowIndex)->GetAt(i)->MakeCString();
			width += dc->GetTextExtent(textEdit->text->GetAt(this->endRowIndex)->GetAt(i)->MakeCString()).cx;
			i++;
		}
		x = 5;
		i = 0;
		rect = { x, this->endRowIndex * textEdit->rowHeight + 5, x + width, this->endRowIndex * textEdit->rowHeight + textEdit->rowHeight + 5 };
		dc->DrawText(cString3, rect, DT_EDITCONTROL | DT_EXPANDTABS);

		textEdit->copyBuffer = cString1 + string2.c_str() + cString3; // 클립보드에 저장
	}
}