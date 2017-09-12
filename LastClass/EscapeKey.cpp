//EscapeKey.cpp

#include "EscapeKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "KeyBoard.h"
#include "KeyAction.h"

EscapeKey::EscapeKey() {
}

EscapeKey::EscapeKey(const EscapeKey& source) {
}

EscapeKey::~EscapeKey() {
}

void EscapeKey::KeyPress(TextEdit *textEdit) {
	// �ؽ�Ʈ����â �������

	if (textEdit->keyBoard->keyAction != 0) {
		delete textEdit->keyBoard->keyAction;
	}
}