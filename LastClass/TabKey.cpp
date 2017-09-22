//TabKey.cpp

#include "TabKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "SingleByteCharacter.h"
#include "HistoryText.h"

TabKey::TabKey() {
}

TabKey::TabKey(const TabKey& source) {
}

TabKey::~TabKey() {
}

void TabKey::KeyPress(TextEdit *textEdit) {
	SingleByteCharacter tab(' ');
	if (textEdit->caret->GetCharacterIndex() == textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength()) {
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Add(tab.Clone());
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Insert(textEdit->caret->GetCharacterIndex(), tab.Clone());
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Insert(textEdit->caret->GetCharacterIndex(), tab.Clone());
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Insert(textEdit->caret->GetCharacterIndex(), tab.Clone());
	}
	else {
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Insert(textEdit->caret->GetCharacterIndex(), tab.Clone());
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Insert(textEdit->caret->GetCharacterIndex(), tab.Clone());
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Insert(textEdit->caret->GetCharacterIndex(), tab.Clone());
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Insert(textEdit->caret->GetCharacterIndex(), tab.Clone());
	}
	textEdit->caret->MoveForwardCharacterIndex();
}