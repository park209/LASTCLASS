//SpaceKey.cpp

#include "SpaceKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "KeyBoard.h"
#include "KeyAction.h"
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

	if (textEdit->keyBoard->keyAction != 0) {
		delete textEdit->keyBoard->keyAction;
	}
}