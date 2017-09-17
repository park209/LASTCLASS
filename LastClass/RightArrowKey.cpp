//RightArrowKey.cpp

#include "RightArrowKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "KeyBoard.h"
#include "KeyAction.h"

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
	if (textEdit->keyBoard->keyAction != 0) {
		delete textEdit->keyBoard->keyAction;
	}
}