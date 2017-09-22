//TextAreaSelected.cpp

#include "TextAreaSelected.h"
#include "TextEdit.h"
#include "Caret.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "Figure.h"

TextAreaSelected::TextAreaSelected() {
}

TextAreaSelected::TextAreaSelected(const TextAreaSelected& source) {
}

TextAreaSelected::~TextAreaSelected() {
}

void TextAreaSelected::SelectTextArea(TextEdit *textEdit, CPaintDC *dc) {
	CRect rect;
	Long startCharacterIndex = 0;
	Long startRowIndex = 0;
	Long endCharacterIndex = 0;
	Long endRowIndex = 0;
	Long i;
	Long x;
	Long width = 0;
	CString str;

	CString cString1;
	if (textEdit->selectedY == textEdit->caret->GetRowIndex()) {
		if (textEdit->selectedX < textEdit->caret->GetCharacterIndex()) {
			startCharacterIndex = textEdit->selectedX;
			startRowIndex = textEdit->selectedY;
			endCharacterIndex = textEdit->caret->GetCharacterIndex();
			endRowIndex = textEdit->caret->GetRowIndex();
		}
		else {
			startCharacterIndex = textEdit->caret->GetCharacterIndex();
			startRowIndex = textEdit->caret->GetRowIndex();
			endCharacterIndex = textEdit->selectedX;
			endRowIndex = textEdit->selectedY;
		}
		width = 0;
		i = startCharacterIndex;
		while (i < endCharacterIndex) { // 첫줄
			cString1 += textEdit->text->GetAt(startRowIndex)->GetAt(i)->MakeCString();
			str = textEdit->text->GetAt(startRowIndex)->GetAt(i)->MakeCString();
			if (str == "\t") {
				str = "        ";
			}
			width += dc->GetTextExtent(str).cx;
			i++;
		}
		x = 5;
		i = 0;
		while (i < startCharacterIndex) { // 현재줄에서 캐릭터인덱스까지 너비 구한다
			str = textEdit->text->GetAt(startRowIndex)->GetAt(i)->MakeCString();
			if (str == "\t") {
				str = "        ";
			}
			x += dc->GetTextExtent(str).cx;
			i++;
		}
		rect = { x, startRowIndex * textEdit->rowHeight + 5, x + width, startRowIndex * textEdit->rowHeight + textEdit->rowHeight + 5 };
		dc->DrawText(cString1, rect, DT_EXPANDTABS | DT_TABSTOP | 0x0800);

		textEdit->copyBuffer = cString1;
	}
	else {
		if (textEdit->selectedY < textEdit->caret->GetRowIndex()) {
			startCharacterIndex = textEdit->selectedX;
			startRowIndex = textEdit->selectedY;
			endCharacterIndex = textEdit->caret->GetCharacterIndex();
			endRowIndex = textEdit->caret->GetRowIndex();
		}
		else {
			startCharacterIndex = textEdit->caret->GetCharacterIndex();
			startRowIndex = textEdit->caret->GetRowIndex();
			endCharacterIndex = textEdit->selectedX;
			endRowIndex = textEdit->selectedY;
		}
		width = 0;
		i = startCharacterIndex;
		while (i < textEdit->text->GetAt(startRowIndex)->GetLength()) { // 첫줄
			cString1 += textEdit->text->GetAt(startRowIndex)->GetAt(i)->MakeCString();
			str = textEdit->text->GetAt(startRowIndex)->GetAt(i)->MakeCString();
			if (str == "\t") {
				str = "        ";
			}
			width += dc->GetTextExtent(str).cx;
			i++;
		}
		cString1 += "\r\n";
		x = 5;
		i = 0;
		while (i < startCharacterIndex) { // 현재줄에서 캐릭터인덱스까지 너비 구한다
			str = textEdit->text->GetAt(startRowIndex)->GetAt(i)->MakeCString();
			if (str == "\t") {
				str = "        ";
			}
			x += dc->GetTextExtent(str).cx;
			i++;
		}
		rect = { x, startRowIndex * textEdit->rowHeight + 5, x + width, startRowIndex * textEdit->rowHeight + textEdit->rowHeight + 5 };
		dc->DrawText(cString1, rect, DT_EXPANDTABS | DT_TABSTOP | 0x0800);

		string string2; // 중간
		if (startRowIndex + 1 < endRowIndex) {
			i = startRowIndex + 1;
			while (i < endRowIndex) {
				string2 += textEdit->text->GetAt(i)->PrintRowString().c_str();
				string2 += "\r\n";
				i++;
			}
			x = 5;
			rect = { x, (startRowIndex + 1) * textEdit->rowHeight + 5, textEdit->GetFigure()->GetX()+ textEdit->GetFigure()->GetWidth(),
				(endRowIndex - 1) * textEdit->rowHeight + textEdit->rowHeight + 5 };
			dc->DrawText(string2.c_str(), rect, DT_EXPANDTABS | DT_TABSTOP | 0x0800);
		}

		CString cString3;
		width = 0;
		i = 0;
		while (i < endCharacterIndex) { // 첫줄
			cString3 += textEdit->text->GetAt(endRowIndex)->GetAt(i)->MakeCString();
			str = textEdit->text->GetAt(endRowIndex)->GetAt(i)->MakeCString();
			if (str == "\t") {
				str = "        ";
			}
			width += dc->GetTextExtent(str).cx;
			i++;
		}
		x = 5;
		i = 0;
		rect = { x, endRowIndex * textEdit->rowHeight + 5, x + width, endRowIndex * textEdit->rowHeight + textEdit->rowHeight + 5 };
		dc->DrawText(cString3, rect, DT_EXPANDTABS | DT_TABSTOP | 0x0800);

		textEdit->copyBuffer = cString1 + string2.c_str() + cString3; // 클립보드에 저장
	}
}