//DoubleClickTextAreaProcess.cpp

#include "DoubleClickTextAreaProcess.h"
#include "TextEdit.h"
#include "Text.h"
#include "Caret.h"
#include "Row.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"

DoubleClickTextAreaProcess::DoubleClickTextAreaProcess() {
}
DoubleClickTextAreaProcess::DoubleClickTextAreaProcess(const DoubleClickTextAreaProcess& source) {
}
DoubleClickTextAreaProcess::~DoubleClickTextAreaProcess() {
}

Long DoubleClickTextAreaProcess::DoubleClickKoreanStartIndex(TextEdit *textEdit) {
	Row *currentRow = textEdit->text->GetAt(textEdit->caret->GetRowIndex());
	Long koreanStartIndex = textEdit->caret->GetCharacterIndex();
	if (koreanStartIndex > 0 && textEdit->caret->GetCharacterIndex() == currentRow->GetLength()) {
		koreanStartIndex--;
	}
	if (koreanStartIndex > 0 && dynamic_cast<DoubleByteCharacter*>(currentRow->GetAt(koreanStartIndex)) &&
			currentRow->GetAt(koreanStartIndex)->MakeCString() != ' ') {
		koreanStartIndex--;
	}
	return koreanStartIndex;
}

//
//Long DoubleClickTextAreaProcess::DoubleClickKoreanEndIndex(TextEdit *textEdit) {
//
//}
//
//Long DoubleClickTextAreaProcess::DoubleClickEnglishStartIndex(TextEdit *textEdit) {
//
//}
//
//Long DoubleClickTextAreaProcess::DoubleClickEnglishEndIndex(TextEdit *textEdit) {
//
//}
