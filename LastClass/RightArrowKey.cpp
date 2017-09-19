//RightArrowKey.cpp

#include "RightArrowKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"

RightArrowKey::RightArrowKey() {
}

RightArrowKey::RightArrowKey(const RightArrowKey& source) {
}

RightArrowKey::~RightArrowKey() {
}

void RightArrowKey::KeyPress(TextEdit *textEdit) {
	textEdit->caret->MoveForwardCharacterIndex();
	if (textEdit->caret->GetCharacterIndex() > textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength()
		&& textEdit->caret->GetRowIndex() == textEdit->text->GetLength() - 1) {
		textEdit->caret->MoveBackwardCharacterIndex();
	}
	else if (textEdit->caret->GetCharacterIndex() > textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength()
		&& textEdit->caret->GetRowIndex() < textEdit->text->GetLength() - 1) {
		textEdit->caret->SetCharacterIndex(0);
		textEdit->caret->MoveForwardRowIndex();
	}
}