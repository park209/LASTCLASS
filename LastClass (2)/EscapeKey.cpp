//EscapeKey.cpp

#include "EscapeKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "KeyBoard.h"
#include "KeyAction.h"

EscapeKey::EscapeKey() {
}

EscapeKey::EscapeKey(const EscapeKey& source) {
}

EscapeKey::~EscapeKey() {
}

void EscapeKey::KeyPress(TextEdit *textEdit) {
	// ÅØ½ºÆ®¿¡µ÷Ã¢ ²¨Áà¾ßÇÔ

	if (textEdit->keyBoard->keyAction != 0) {
		delete textEdit->keyBoard->keyAction;
	}
}