//DeleteKey.cpp

#include "DeleteKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"

DeleteKey::DeleteKey() {
}

DeleteKey::DeleteKey(const DeleteKey& source) {
}

DeleteKey::~DeleteKey() {
}

void DeleteKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->caret->GetCharacterIndex() < textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength()) {
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Remove(textEdit->caret->GetCharacterIndex());
	}
	else if (textEdit->caret->GetCharacterIndex() == textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength()
		&& textEdit->caret->GetRowIndex() < textEdit->text->GetLength() - 1) {
		Long i = 0;
		while (i < textEdit->text->GetAt(textEdit->caret->GetRowIndex() + 1)->GetLength()) {
			textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Add(textEdit->text->GetAt(textEdit->caret->GetRowIndex() + 1)->GetAt(i));
			i++;
		}
		textEdit->text->Remove(textEdit->caret->GetRowIndex() + 1);
	}
}

