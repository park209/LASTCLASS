//BackSpaceKey.cpp

#include "BackSpaceKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Character.h"
#include "HistoryText.h"
#include "TextAreaSelected.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"

BackSpaceKey::BackSpaceKey() {
}

BackSpaceKey::BackSpaceKey(const BackSpaceKey& source) {
}

BackSpaceKey::~BackSpaceKey() {
}

void BackSpaceKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->flagSelection == 1) {
		Long i = 0;
		if (textEdit->textAreaSelected->GetStartRowIndex() == textEdit->textAreaSelected->GetEndRowIndex()) {
			textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
			while (i < textEdit->textAreaSelected->GetEndCharacterIndex() - textEdit->textAreaSelected->GetStartCharacterIndex()) {
				textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex())->Remove(textEdit->textAreaSelected->GetStartCharacterIndex());
				i++;
			}
		}
		else if (textEdit->textAreaSelected->GetStartRowIndex() < textEdit->textAreaSelected->GetEndRowIndex()) { // 여러줄이면
			textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
			while (textEdit->textAreaSelected->GetStartCharacterIndex() < textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex())->GetLength()) {//첫줄
				textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex())->Remove(textEdit->textAreaSelected->GetStartCharacterIndex());
			}
			i = 0;
			while (i < textEdit->textAreaSelected->GetEndRowIndex() - textEdit->textAreaSelected->GetStartRowIndex() - 1) { // 중간줄 있으면 중간줄
				textEdit->text->Remove(textEdit->textAreaSelected->GetStartRowIndex() + 1);
				i++;
			}
			i = 0; // 제일 아랫줄
			while (i < textEdit->textAreaSelected->GetEndCharacterIndex()) {
				textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->Remove(0);
				i++;
			}
			// 맨 아랫줄 남은거 복사해다가 스타트로우에 붙여넣고 밑에꺼 지워버린다
			i = 0;
			while (i < textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->GetLength() - textEdit->textAreaSelected->GetEndCharacterIndex()) {
				if (dynamic_cast<DoubleByteCharacter*>(textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->GetAt(i))) {
					DoubleByteCharacter *tempDouble = static_cast<DoubleByteCharacter*>(textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->GetAt(i));
					textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex())->Add(tempDouble->Clone());
					i++;
				}
				else if (dynamic_cast<SingleByteCharacter*>(textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->GetAt(i))) {
					SingleByteCharacter *tempSingle = static_cast<SingleByteCharacter*>(textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->GetAt(i));
					textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex())->Add(tempSingle->Clone());
					i++;
				}
			}
			textEdit->text->Remove(textEdit->textAreaSelected->GetStartRowIndex() + 1);
		}
		textEdit->caret->SetRowIndex(textEdit->textAreaSelected->GetStartRowIndex());
		textEdit->caret->SetCharacterIndex(textEdit->textAreaSelected->GetStartCharacterIndex());
		textEdit->flagSelection = 0;
	}
	else {
		if (textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength() > 0 && textEdit->caret->GetCharacterIndex() > 0) {
			textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
			textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Remove(textEdit->caret->GetCharacterIndex() - 1);
			textEdit->caret->MoveBackwardCharacterIndex();
		}
		else if (textEdit->caret->GetCharacterIndex() == 0 && textEdit->caret->GetRowIndex() > 0) {
			textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
			if (textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength() == 0) {
				textEdit->text->Remove(textEdit->caret->GetRowIndex());
				textEdit->caret->MoveBackwardRowIndex();
				textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength());
			}
			else {
				textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex() - 1)->GetLength());
				while (textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength() > 0) {
					Character *character = textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetAt(0);
					textEdit->text->GetAt(textEdit->caret->GetRowIndex() - 1)->Add(character->Clone());
					textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Remove(0);
				}
				textEdit->text->Remove(textEdit->caret->GetRowIndex());
				textEdit->caret->MoveBackwardRowIndex();
			}
		}
	}
}