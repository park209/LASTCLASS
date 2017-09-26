//DeleteTextAreaSelected.cpp

#include "DeleteTextAreaSelected.h"
#include "TextEdit.h"
#include "TextAreaSelected.h"
#include "Text.h"
#include "Row.h"
#include "DoubleByteCharacter.h"
#include "SingleByteCharacter.h"


DeleteTextAreaSelected::DeleteTextAreaSelected() {
}

DeleteTextAreaSelected::DeleteTextAreaSelected(const DeleteTextAreaSelected& source) {
}

DeleteTextAreaSelected::~DeleteTextAreaSelected() {
}

void DeleteTextAreaSelected::DeleteSingleLineSelected(TextEdit* textEdit) {
	Long i = 0;
	while (i < textEdit->textAreaSelected->GetEndCharacterIndex() - textEdit->textAreaSelected->GetStartCharacterIndex()) {
		textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex())->Remove(textEdit->textAreaSelected->GetStartCharacterIndex());
		i++;
	}
}

void DeleteTextAreaSelected::DeleteFirstMultiLineSelected(TextEdit* textEdit) {
	while (textEdit->textAreaSelected->GetStartCharacterIndex() < 
			textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex())->GetLength()) {//첫줄
		textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex())->Remove(textEdit->textAreaSelected->GetStartCharacterIndex());
	}
}

void DeleteTextAreaSelected::DeleteMiddleMultiLineSelected(TextEdit* textEdit) {
	Long i = 0;
	while (i < textEdit->textAreaSelected->GetEndRowIndex() - textEdit->textAreaSelected->GetStartRowIndex() - 1) { // 중간줄 있으면 중간줄
		textEdit->text->Remove(textEdit->textAreaSelected->GetStartRowIndex() + 1);
		i++;
	}
}

void DeleteTextAreaSelected::DeleteEndMultiLineSelected(TextEdit* textEdit) {
	Long i = 0; // 제일 아랫줄
	while (i < textEdit->textAreaSelected->GetEndCharacterIndex()) {
		textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->Remove(0);
		i++;
	}
}

void DeleteTextAreaSelected::ConnectRemains(TextEdit *textEdit, Long copyCount) {
	Long i = 0;
	while (i < copyCount) {
		if (dynamic_cast<DoubleByteCharacter*>(textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->GetAt(i))) {
			DoubleByteCharacter *tempDouble = static_cast<DoubleByteCharacter*>(textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->GetAt(i));
			textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex())->Add(tempDouble->Clone());
		}
		else if (dynamic_cast<SingleByteCharacter*>(textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->GetAt(i))) {
			SingleByteCharacter *tempSingle = static_cast<SingleByteCharacter*>(textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->GetAt(i));
			textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex())->Add(tempSingle->Clone());
		}
		i++;
	}
	textEdit->text->Remove(textEdit->textAreaSelected->GetStartRowIndex() + 1);
}