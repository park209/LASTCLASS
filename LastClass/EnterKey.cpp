//EnterKey.cpp

#include "EnterKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "KeyBoard.h"
#include "KeyAction.h"

EnterKey::EnterKey() {
}

EnterKey::EnterKey(const EnterKey& source) {
}

EnterKey::~EnterKey() {
}

void EnterKey::KeyPress(TextEdit *textEdit) {
	// �ؽ�Ʈ����â �������
	if (GetKeyState(VK_CONTROL) >= 0) {
		//CFrameWnd::OnClose();
	}

	if (textEdit->keyBoard->keyAction != 0) {
		delete textEdit->keyBoard->keyAction;
	}
}