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
	// �ؽ�Ʈ����â �������
	if (GetKeyState(VK_CONTROL) >= 0) {
		//textEdit->DestroyWindow();
	}
}