//HomeKey.cpp

#include "HomeKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"

HomeKey::HomeKey() {
}
HomeKey::HomeKey(const HomeKey& source) {
}
HomeKey::~HomeKey() {
}
void HomeKey::KeyPress(TextEdit *textEdit) {
	if (GetKeyState(VK_SHIFT) >= 0) {
		if (textEdit->flagSelection == 1) {
			textEdit->flagSelection = 0;
		}
	}
	else {
		if (textEdit->flagSelection == 0) {
			textEdit->flagSelection = 1;
			textEdit->selectedX = textEdit->caret->GetCharacterIndex();
			textEdit->selectedRowIndex = textEdit->caret->GetRowIndex();
		}
	}
	textEdit->caret->SetCharacterIndex(0);
}