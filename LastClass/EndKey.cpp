//EndKey.cpp

#include "EndKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"

EndKey::EndKey() {
}
EndKey::EndKey(const EndKey& source) {
}
EndKey::~EndKey() {
}
void EndKey::KeyPress(TextEdit *textEdit) {
	textEdit->characterIndex = textEdit->text->GetAt(textEdit->GetRowIndex())->GetLength();
}