//CtrlCopyKey.cpp

#include "CtrlCopyKey.h"
#include "TextEdit.h"

CtrlCopyKey::CtrlCopyKey() {
}
CtrlCopyKey::CtrlCopyKey(const CtrlCopyKey& source) {
}
CtrlCopyKey::~CtrlCopyKey() {
}

void CtrlCopyKey::KeyPress(TextEdit *textEdit) {
	if (GetKeyState(VK_CONTROL) < 0) {

		
	}
}