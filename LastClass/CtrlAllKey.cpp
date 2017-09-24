//CtrlAllKey.cpp

#include "CtrlAllKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"

CtrlAllKey::CtrlAllKey() {
}
CtrlAllKey::CtrlAllKey(const CtrlAllKey& source) {
}
CtrlAllKey::~CtrlAllKey() {
}
void CtrlAllKey::KeyPress(TextEdit *textEdit) {
	if (GetKeyState(VK_CONTROL) < 0) {
		textEdit->selectedX = 0;
		textEdit->selectedRowIndex = 0;
		textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->text->GetLength() - 1)->GetLength());
		textEdit->caret->SetRowIndex(textEdit->text->GetLength()-1);

		textEdit->flagSelection = 1;
	}
}