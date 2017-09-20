//HomeKey.cpp

#include "HomeKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"

HomeKey::HomeKey() {
}
HomeKey::HomeKey(const HomeKey& source) {
}
HomeKey::~HomeKey() {
}
void HomeKey::KeyPress(TextEdit *textEdit) {
	textEdit->caret->SetCharacterIndex(0);
}