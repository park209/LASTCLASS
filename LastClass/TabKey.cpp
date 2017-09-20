//TabKey.cpp

#include "TabKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "KeyBoard.h"
#include "KeyAction.h"

TabKey::TabKey() {
}

TabKey::TabKey(const TabKey& source) {
}

TabKey::~TabKey() {
}

void TabKey::KeyPress(TextEdit *textEdit) {

	if (textEdit->keyBoard->keyAction != 0) {
		delete textEdit->keyBoard->keyAction;
	}
}