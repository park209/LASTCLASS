//LeftArrowKey.cpp

#include "LeftArrowKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"

LeftArrowKey::LeftArrowKey() {
}

LeftArrowKey::LeftArrowKey(const LeftArrowKey& source) {
}

LeftArrowKey::~LeftArrowKey() {
}

void LeftArrowKey::KeyPress(TextEdit *textEdit) {
	textEdit->characterIndex--;
	if (textEdit->characterIndex < 0) {
		textEdit->characterIndex++;
	}
}