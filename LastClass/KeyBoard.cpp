//KeyBoard.cpp

#include "KeyBoard.h"
#include "KeyAction.h"
#include "DeleteKey.h"
#include "BackSpaceKey.h"
#include "LeftArrowKey.h"
#include "RightArrowKey.h"
#include "UpArrowKey.h"
#include "DownArrowKey.h"
#include "SpaceKey.h"
#include "CtrlEnterKey.h"
#include "HomeKey.h"
#include "EndKey.h"
#include "InsertKey.h"
#include "EscapeKey.h"
#include "EnterKey.h"
#include "TabKey.h"

KeyBoard::KeyBoard() {
	this->keyAction = 0;
}

KeyBoard::KeyBoard(const KeyBoard& source) {
	this->keyAction = 0; //임시로 clone만들면 아래꺼로
						 //this->keyAction = const_cast<KeyBoard>(source).keyAction.Clone();
}

KeyBoard::~KeyBoard() {
	if (this->keyAction != 0) {
		delete this->keyAction;
	}
}

KeyBoard& KeyBoard::operator = (const KeyBoard& source) {
	this->keyAction = 0;
	//this->keyAction = const_cast<KeyBoard>(source).keyAction.Clone();
	return *this;
}

void KeyBoard::KeyDown(TextEdit *textEdit, UINT nChar, UINT nRepCnt, UINT nFlags) {
	/*if (this->keyAction != NULL) {
		delete this->keyAction;
	}*/
	switch (nChar) {
	case VK_DELETE:
		this->keyAction = new DeleteKey;
		this->keyAction->KeyPress(textEdit);
		break;
	case VK_BACK: // 백스페이스
		this->keyAction = new BackSpaceKey;
		this->keyAction->KeyPress(textEdit);
		break;
	case VK_LEFT:
		this->keyAction = new LeftArrowKey;
		this->keyAction->KeyPress(textEdit);
		break;
	case VK_RIGHT:
		this->keyAction = new RightArrowKey;
		this->keyAction->KeyPress(textEdit);
		break;
	case VK_UP:
		this->keyAction = new UpArrowKey;
		this->keyAction->KeyPress(textEdit);
		break;
	case VK_DOWN:
		this->keyAction = new DownArrowKey;
		this->keyAction->KeyPress(textEdit);
		break;
	case VK_SPACE:
		this->keyAction = new SpaceKey;
		this->keyAction->KeyPress(textEdit);
		break;
	case VK_RETURN: // 컨트롤 엔터
		if (GetKeyState(VK_CONTROL) >= 0) {
			this->keyAction = new EnterKey;
			this->keyAction->KeyPress(textEdit);
		}
		else if (GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new CtrlEnterKey;
			this->keyAction->KeyPress(textEdit);
		}
		break;
	case VK_HOME:
		this->keyAction = new HomeKey;
		this->keyAction->KeyPress(textEdit);
		break;
	case VK_END:
		this->keyAction = new EndKey;
		this->keyAction->KeyPress(textEdit);
		break;
	case VK_INSERT:
		this->keyAction = new InsertKey;
		this->keyAction->KeyPress(textEdit);
		break;
	case VK_TAB:
		this->keyAction = new TabKey;
		this->keyAction->KeyPress(textEdit);
		break;
	case VK_ESCAPE:
		this->keyAction = new EscapeKey;
		this->keyAction->KeyPress(textEdit);
		break;
	default:break;
	}
}