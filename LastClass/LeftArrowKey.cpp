//LeftArrowKey.cpp

#include "LeftArrowKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"

LeftArrowKey::LeftArrowKey() {
}

LeftArrowKey::LeftArrowKey(const LeftArrowKey& source) {
}

LeftArrowKey::~LeftArrowKey() {
}

void LeftArrowKey::KeyPress(TextEdit *textEdit) {
	textEdit->caret->MoveBackwardCharacterIndex();
	if (textEdit->caret->GetCharacterIndex() < 0
		&& textEdit->caret->GetRowIndex() == 0) {
		textEdit->caret->MoveForwardCharacterIndex();
	}
	else if (textEdit->caret->GetCharacterIndex() < 0
		&& textEdit->caret->GetRowIndex() > 0) {
		textEdit->caret->MoveBackwardRowIndex();
		textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength());

	}
}