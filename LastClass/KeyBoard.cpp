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
#include "TextEdit.h"
#include "PlusKey.h"
#include "MinusKey.h"
#include "CtrlCopyKey.h"
#include "CtrlAllKey.h"

KeyBoard::KeyBoard() {
	this->keyAction = 0;
}

KeyBoard::KeyBoard(const KeyBoard& source) {
	this->keyAction = 0; //�ӽ÷� clone����� �Ʒ�����
						 //this->keyAction = const_cast<KeyBoard>(source).keyAction.Clone();
}

KeyBoard::~KeyBoard() {
	if (this->keyAction != 0) {
		delete this->keyAction;
		this->keyAction = 0;
	}
}

KeyBoard& KeyBoard::operator = (const KeyBoard& source) {
	this->keyAction = 0;
	//this->keyAction = const_cast<KeyBoard>(source).keyAction.Clone();
	return *this;
}

KeyAction* KeyBoard::KeyDown(TextEdit *textEdit, UINT nChar, UINT nRepCnt, UINT nFlags) {
	/*if (textEdit->flagSelection == 1) {
	textEdit->flagSelection = 0;
	}*/
	switch (nChar) {
	case VK_DELETE:
		this->keyAction = new DeleteKey;
		break;
	case VK_BACK: // �齺���̽�
		this->keyAction = new BackSpaceKey;
		break;
	case VK_LEFT:
		this->keyAction = new LeftArrowKey;
		break;
	case VK_RIGHT:
		this->keyAction = new RightArrowKey;
		break;
	case VK_UP:
		this->keyAction = new UpArrowKey;
		break;
	case VK_DOWN:
		this->keyAction = new DownArrowKey;
		break;
	case VK_SPACE:
		this->keyAction = new SpaceKey;
		break;
	case VK_RETURN: // ��Ʈ�� ����
		if (GetKeyState(VK_CONTROL) >= 0) {
			this->keyAction = new EnterKey;
		}
		else if (GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new CtrlEnterKey;
		}
		break;
	case VK_HOME:
		this->keyAction = new HomeKey;
		break;
	case VK_END:
		this->keyAction = new EndKey;
		break;
	case VK_INSERT:
		this->keyAction = new InsertKey;
		break;
	case VK_TAB:
		this->keyAction = new TabKey;
		break;
	case VK_ESCAPE:
		this->keyAction = new EscapeKey;
		break;
	case  VK_OEM_PLUS:
		this->keyAction = new PlusKey;
		break;
	case VK_OEM_MINUS:
		this->keyAction = new MinusKey;
		break;
	case 67:
		this->keyAction = new CtrlCopyKey;
		break;
	case 65:
		this->keyAction = new CtrlAllKey;
		break;
	default:
		this->keyAction = 0;
		break;
	}
	return this->keyAction;
}