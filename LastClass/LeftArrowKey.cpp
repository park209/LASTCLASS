//LeftArrowKey.cpp

#include "LeftArrowKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "KeyBoard.h"
#include "KeyAction.h"

LeftArrowKey::LeftArrowKey() {
}

LeftArrowKey::LeftArrowKey(const LeftArrowKey& source) {
}

LeftArrowKey::~LeftArrowKey() {
}

void LeftArrowKey::KeyPress(TextEdit *textEdit) {
	textEdit->characterIndex--;
	if (textEdit->characterIndex < 0) {
		textEdit->characterIndex = 0;
	}
	if (textEdit->keyBoard->keyAction != 0) {
		delete textEdit->keyBoard->keyAction;
	}
}