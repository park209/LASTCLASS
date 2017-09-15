//DeleteKey.cpp

#include "DeleteKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"

DeleteKey::DeleteKey() {
}

DeleteKey::DeleteKey(const DeleteKey& source) {
}

DeleteKey::~DeleteKey() {
}

void DeleteKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->GetCharacterIndex() < textEdit->text->GetAt(textEdit->GetRowIndex())->GetLength()) {
		textEdit->text->GetAt(textEdit->GetRowIndex())->Remove(textEdit->GetCharacterIndex());
	}
}

