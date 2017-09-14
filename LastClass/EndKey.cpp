//EndKey.cpp

#include "EndKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "KeyBoard.h"
#include "KeyAction.h"

EndKey::EndKey() {
}

EndKey::EndKey(const EndKey& source) {
}

EndKey::~EndKey() {
}

void EndKey::KeyPress(TextEdit *textEdit) {
	textEdit->characterIndex = textEdit->text->GetAt(textEdit->GetRowIndex())->GetLength();

	if (textEdit->keyBoard->keyAction != 0) {
		delete textEdit->keyBoard->keyAction;
	}
}