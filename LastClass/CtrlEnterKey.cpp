//CtrlEnterKey.cpp

#include "CtrlEnterKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Character.h"

CtrlEnterKey::CtrlEnterKey() {
}
CtrlEnterKey::CtrlEnterKey(const CtrlEnterKey& source) {
}
CtrlEnterKey::~CtrlEnterKey() {
}

void CtrlEnterKey::KeyPress(TextEdit *textEdit) {
	if (GetKeyState(VK_CONTROL) < 0) {
		Row row;
		//if (!GetKeyState(VK_RETURN)) {

		if (textEdit->caret->GetCharacterIndex() == 0) {
			textEdit->text->InsertRow(textEdit->caret->GetRowIndex(),row.Clone());
			textEdit->caret->MoveForwardRowIndex();
			textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength());
		}
		else {
			textEdit->text->InsertRow(textEdit->caret->GetRowIndex() + 1, row.Clone());
			textEdit->caret->MoveForwardRowIndex();
			Long j = 0;
			while (textEdit->caret->GetCharacterIndex() < textEdit->text->GetAt(textEdit->caret->GetRowIndex() - 1)->GetLength()) {
				Character *character = textEdit->text->GetAt(textEdit->caret->GetRowIndex() - 1)->GetAt(textEdit->caret->GetCharacterIndex());
				textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Add(character->Clone());
				textEdit->text->GetAt(textEdit->caret->GetRowIndex() - 1)->Remove(textEdit->caret->GetCharacterIndex());
			}
			textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength());

		}
		textEdit->caret->SetCharacterIndex(0);
	}
}