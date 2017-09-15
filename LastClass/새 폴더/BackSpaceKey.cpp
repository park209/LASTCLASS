//BackSpaceKey.cpp

#include "BackSpaceKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "KeyBoard.h"
#include "KeyAction.h"

BackSpaceKey::BackSpaceKey() {
}

BackSpaceKey::BackSpaceKey(const BackSpaceKey& source) {
}

BackSpaceKey::~BackSpaceKey() {
}

void BackSpaceKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->text->GetAt(textEdit->GetRowIndex())->GetLength() > 0 && textEdit->GetCharacterIndex() > 0) {
		textEdit->text->GetAt(textEdit->GetRowIndex())->Remove(textEdit->GetCharacterIndex() - 1);
		(textEdit->characterIndex)--;
	}
}