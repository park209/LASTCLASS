//HomeKey.cpp

#include "HomeKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "KeyBoard.h"
#include "KeyAction.h"

HomeKey::HomeKey() {
}

HomeKey::HomeKey(const HomeKey& source) {
}

HomeKey::~HomeKey() {
}

void HomeKey::KeyPress(TextEdit *textEdit) {
	textEdit->characterIndex = 0;

	if (textEdit->keyBoard->keyAction != 0) {
		delete textEdit->keyBoard->keyAction;
	}
}