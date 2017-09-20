// MinusKey.cpp

#include "MinusKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"

MinusKey::MinusKey() {
}

MinusKey::MinusKey(const MinusKey& source) {
}

MinusKey::~MinusKey() {
}

void MinusKey::KeyPress(TextEdit *textEdit) {
	if (GetKeyState(VK_RSHIFT) < 0) { //ÆùÆ® size
		textEdit->rowHeight--;
	}
}