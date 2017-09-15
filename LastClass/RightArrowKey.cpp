//RightArrowKey.cpp

#include "RightArrowKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"

RightArrowKey::RightArrowKey() {
}

RightArrowKey::RightArrowKey(const RightArrowKey& source) {
}

RightArrowKey::~RightArrowKey() {
}

void RightArrowKey::KeyPress(TextEdit *textEdit) {
	textEdit->characterIndex++;
	if (textEdit->characterIndex > textEdit->text->GetAt(textEdit->rowIndex)->GetLength()) {
		textEdit->characterIndex = textEdit->text->GetAt(textEdit->rowIndex)->GetLength();
	}
}