//BackSpaceKey.cpp

#include "BackSpaceKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Character.h"
#include "HistoryText.h"

BackSpaceKey::BackSpaceKey() {
}

BackSpaceKey::BackSpaceKey(const BackSpaceKey& source) {
}

BackSpaceKey::~BackSpaceKey() {
}

void BackSpaceKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength() > 0 &&textEdit->caret->GetCharacterIndex() > 0) {
		textEdit->historyText->PushUndo(textEdit->text);
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Remove(textEdit->caret->GetCharacterIndex() - 1);
		textEdit->caret->MoveBackwardCharacterIndex();
	}
	else if (textEdit->caret->GetCharacterIndex() == 0 && textEdit->caret->GetRowIndex() > 0) {
		textEdit->historyText->PushUndo(textEdit->text);
		if (textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength() == 0) {
			textEdit->text->Remove(textEdit->caret->GetRowIndex());
			textEdit->caret->MoveBackwardRowIndex();
			textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength());
		}
		else {
			while (textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength()>0) {
				Character *character = textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetAt(0);
				textEdit->text->GetAt(textEdit->caret->GetRowIndex() - 1)->Add(character->Clone());
				textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Remove(0);
			}
			textEdit->text->Remove(textEdit->caret->GetRowIndex());
			textEdit->caret->MoveBackwardRowIndex();
			textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength());
		}
	}
}