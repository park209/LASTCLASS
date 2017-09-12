//CtrlEnterKey.cpp

#include "CtrlEnterKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "KeyBoard.h"
#include "KeyAction.h"

CtrlEnterKey::CtrlEnterKey() {
}

CtrlEnterKey::CtrlEnterKey(const CtrlEnterKey& source) {
}

CtrlEnterKey::~CtrlEnterKey() {
}

void CtrlEnterKey::KeyPress(TextEdit *textEdit) {
	if (GetKeyState(VK_CONTROL) < 0) {
		textEdit->rowIndex = textEdit->classDiagramForm->text->InsertRow(textEdit->GetFormX(), textEdit->GetFormY(), textEdit->GetRowHeight(), textEdit->GetRowIndex());
		while (textEdit->characterIndex < textEdit->classDiagramForm->text->GetAt(textEdit->GetRowIndex() - 1)->GetLength()) {
			Character *character = textEdit->classDiagramForm->text->GetAt(textEdit->GetRowIndex() - 1)->GetAt(textEdit->characterIndex);

			textEdit->classDiagramForm->text->GetAt(textEdit->GetRowIndex())->Add(character->Clone());
			textEdit->classDiagramForm->text->GetAt(textEdit->GetRowIndex() - 1)->Remove(textEdit->GetCharacterIndex());
		}
		Long i = textEdit->GetRowIndex() + 1;
		while (i < textEdit->classDiagramForm->text->GetLength()) {
			/*textEdit->classDiagramForm->text->Modify(textEdit->classDiagramForm->text->GetAt(i)->GetX(), textEdit->classDiagramForm->text->GetAt(i)->GetY() + textEdit->GetRowHeight(),
				textEdit->classDiagramForm->text->GetAt(i)->Clone());
			i++;*/
		}
		textEdit->characterIndex = 0;
	}

	if (textEdit->keyBoard->keyAction != 0) {
		delete textEdit->keyBoard->keyAction;
	}
}