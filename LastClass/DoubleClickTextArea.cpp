//DoubleClickTextArea.cpp

#include "DoubleClickTextArea.h"
#include "TextEdit.h"
#include "DoubleClickTextAreaProcess.h"
#include "Caret.h"

DoubleClickTextArea::DoubleClickTextArea() {
}
DoubleClickTextArea::DoubleClickTextArea(const DoubleClickTextArea& source) {
}
DoubleClickTextArea::~DoubleClickTextArea() {
}

void DoubleClickTextArea::FindDoubleClickAreaIndex(TextEdit *textEdit) {
	DoubleClickTextAreaProcess *findProcess = new DoubleClickTextAreaProcess();

	Long startCharacterIndex = findProcess->DoubleClickStartIndex(textEdit);
	Long endCharacterIndex = findProcess->DoubleClickEndIndex(textEdit);

	if (textEdit->flagSelection == 0) {
		textEdit->flagSelection = 1;
	}
	textEdit->selectedCharacterIndex = startCharacterIndex;
	textEdit->selectedRowIndex = textEdit->caret->GetRowIndex();
	textEdit->caret->SetCharacterIndex(endCharacterIndex);
	textEdit->caret->SetRowIndex(textEdit->caret->GetRowIndex());
}