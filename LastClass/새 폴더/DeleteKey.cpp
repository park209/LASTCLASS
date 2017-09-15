//DeleteKey.cpp

#include "DeleteKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "KeyBoard.h"
#include "KeyAction.h"

DeleteKey::DeleteKey() {
}

DeleteKey::DeleteKey(const DeleteKey& source) {
}

DeleteKey::~DeleteKey() {
}

void DeleteKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->count > 0 && textEdit->GetCharacterIndex() < textEdit->text->GetAt(textEdit->GetRowIndex())->GetLength()) {
		textEdit->text->GetAt(textEdit->GetRowIndex())->Remove(textEdit->GetCharacterIndex());
	}
}

