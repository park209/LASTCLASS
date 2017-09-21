//SpaceKey.cpp

#include "SpaceKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "SingleByteCharacter.h"
#include "HistoryText.h"

SpaceKey::SpaceKey() {
}

SpaceKey::SpaceKey(const SpaceKey& source) {
}

SpaceKey::~SpaceKey() {
}

void SpaceKey::KeyPress(TextEdit *textEdit) {
	SingleByteCharacter spaceText(' ');
	textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Insert(textEdit->caret->GetCharacterIndex(), spaceText.Clone());
	textEdit->caret->MoveForwardCharacterIndex();
}