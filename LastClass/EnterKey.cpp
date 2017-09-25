//EnterKey.cpp

#include "EnterKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"

EnterKey::EnterKey() {
}
EnterKey::EnterKey(const EnterKey& source) {
}
EnterKey::~EnterKey() {
}
void EnterKey::KeyPress(TextEdit *textEdit) {
	// ÅØ½ºÆ®¿¡µ÷Ã¢ ²¨Áà¾ßÇÔ
	if (GetKeyState(VK_CONTROL) >= 0) {
		textEdit->OnClose();
	}
}