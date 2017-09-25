//DeleteTextArea.cpp

#include "DeleteTextArea.h"
#include "DeleteTextAreaSelected.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "TextAreaSelected.h"
#include "HistoryText.h"
#include "Caret.h"

DeleteTextArea::DeleteTextArea() {
}
DeleteTextArea::DeleteTextArea(const DeleteTextArea& source) {
}
DeleteTextArea::~DeleteTextArea() {
}

void DeleteTextArea::DeleteArea(TextEdit *textEdit) {
	DeleteTextAreaSelected *deleteLines = new DeleteTextAreaSelected();
	Long i = 0;
	if (textEdit->textAreaSelected->GetStartRowIndex() == textEdit->textAreaSelected->GetEndRowIndex()) {
		textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
		deleteLines->DeleteSingleLineSelected(textEdit);
	}
	else if (textEdit->textAreaSelected->GetStartRowIndex() < textEdit->textAreaSelected->GetEndRowIndex()) { // 여러줄이면
		textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
		deleteLines->DeleteFirstMultiLineSelected(textEdit);
		deleteLines->DeleteMiddleMultiLineSelected(textEdit);
		Long copyCount = textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->GetLength() - textEdit->textAreaSelected->GetEndCharacterIndex();
		deleteLines->DeleteEndMultiLineSelected(textEdit);
		deleteLines->ConnectRemains(textEdit, copyCount);
	}
	textEdit->caret->SetRowIndex(textEdit->textAreaSelected->GetStartRowIndex());
	textEdit->caret->SetCharacterIndex(textEdit->textAreaSelected->GetStartCharacterIndex());
	textEdit->flagSelection = 0;
}