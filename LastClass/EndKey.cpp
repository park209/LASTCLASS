//EndKey.cpp

#include "EndKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Figure.h"
#include "Caret.h"
#include "KeyBoard.h"
#include <afxwin.h>

EndKey::EndKey() {
}
EndKey::EndKey(const EndKey& source) {
}
EndKey::~EndKey() {
}
void EndKey::KeyPress(TextEdit *textEdit) {
	textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength());
}