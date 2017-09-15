//HomeKey.cpp

#include "HomeKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"

HomeKey::HomeKey() {
}
HomeKey::HomeKey(const HomeKey& source) {
}
HomeKey::~HomeKey() {
}
void HomeKey::KeyPress(TextEdit *textEdit) {
	textEdit->characterIndex = 0;
}