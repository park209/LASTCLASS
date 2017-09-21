//CtrlUndoKey.cpp

#include "CtrlUndoKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "HistoryText.h"

CtrlUndoKey::CtrlUndoKey() {
}
CtrlUndoKey::CtrlUndoKey(const CtrlUndoKey& source) {
}
CtrlUndoKey::~CtrlUndoKey() {
}
void CtrlUndoKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->historyText->undoArray->GetLength() > 0) {
		Text *text_ = textEdit->historyText->PopUndo();

		delete[] textEdit->text;
		textEdit->text = text_;
	}
}