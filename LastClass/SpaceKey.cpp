//SpaceKey.cpp

#include "SpaceKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "SingleByteCharacter.h"

SpaceKey::SpaceKey() {
}

SpaceKey::SpaceKey(const SpaceKey& source) {
}

SpaceKey::~SpaceKey() {
}

void SpaceKey::KeyPress(TextEdit *textEdit) {
	SingleByteCharacter spaceText(' ');
	textEdit->text->GetAt(textEdit->GetRowIndex())->Insert(textEdit->GetCharacterIndex(), spaceText.Clone());
	textEdit->characterIndex++;
}