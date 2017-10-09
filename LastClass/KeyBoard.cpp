//KeyBoard.cpp

#include "KeyBoard.h"
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
#include "CtrlPasteKey.h"
#include "CtrlUndoTextKey.h"
#include "CtrlRedoTextKey.h"
#include "CtrlCutKey.h"
#include "ClassDiagramForm.h"
#include "AddTemplateKey.h"
#include "DeleteGraphicKey.h"
#include "AddReceptionKey.h"
#include "RemoveReceptionKey.h"
#include "AddAttributeKey.h"
#include "AddAttributeKey.h"
#include "RemoveAttributeKey.h"
#include "AddMethodKey.h"
#include "RemoveMethodKey.h"
#include "RemoveTemplateKey.h"
#include "GraphicCtrlUndoKey.h"
#include "GraphicCtrlRedoKey.h"
#include "GraphicCtrlAllKey.h"

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
		this->keyAction = 0;
	}
}

KeyBoard& KeyBoard::operator = (const KeyBoard& source) {
	this->keyAction = 0;

	return *this;
}

KeyAction* KeyBoard::KeyDown(TextEdit *textEdit, UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->keyAction != 0) {
		delete this->keyAction;
		this->keyAction = 0;
	}
	switch (nChar) {
	case VK_DELETE:
		this->keyAction = new DeleteKey;
		break;
	case VK_BACK: // 백스페이스
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
	case VK_RETURN: // 컨트롤 엔터
		if (nFlags && GetKeyState(VK_CONTROL) >= 0) {
			this->keyAction = new EnterKey;
		}
		else if (nFlags && GetKeyState(VK_CONTROL) < 0) {
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
		if (nFlags && GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new PlusKey;
		}
		break;
	case VK_OEM_MINUS:
		if (nFlags && GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new MinusKey;
		}
		break;
	case 67:
		if (nFlags && GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new CtrlCopyKey;
		}
		break;
	case 0x41:
		if (nFlags && GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new CtrlAllKey;
		}
		break;
	case 0x56:
		if (nFlags && GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new CtrlPasteKey;
		}
		break;
	case 88:
		if (nFlags && GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new CtrlCutKey;
		}
		break;
	case 90:
		if (nFlags && GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new CtrlUndoTextKey;
		}
		break;
	case 89:
		if (nFlags && GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new CtrlRedoTextKey;
		}
		break;
	default:
		break;
	}
	return this->keyAction;
}

KeyAction* KeyBoard::KeyDown(ClassDiagramForm *classDiagramForm, UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->keyAction != 0) {
		delete this->keyAction;
		this->keyAction = 0;
	}
	switch (nChar) {
	case VK_DELETE:
		this->keyAction = new DeleteGraphicKey;
		break;
	case 0x59: // y
		if (nFlags && GetKeyState(VK_CONTROL) >= 0) {
			//this->keyAction = new ;
		}
		else if (nFlags && GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new GraphicCtrlRedoKey;
		}
		break;
	case 0x41: // a
		if (nFlags && GetKeyState(VK_CONTROL) >= 0) {
			this->keyAction = new AddTemplateKey;
		}
		else if (nFlags && GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new GraphicCtrlAllKey;
		}
		break;
	case 0x46: // f 
		this->keyAction = new AddReceptionKey;
		break;
	case 0x53: // s 
		this->keyAction = new AddAttributeKey;
		break;
	case 0x44: // d
		this->keyAction = new AddMethodKey;
		break;
	case 0x5A: // z
		if (nFlags && GetKeyState(VK_CONTROL) >= 0) {
			this->keyAction = new RemoveTemplateKey;
		}
		else if (nFlags && GetKeyState(VK_CONTROL) < 0) {
			this->keyAction = new GraphicCtrlUndoKey;
		}
		break;
	case 0x56: // x
		this->keyAction = new RemoveReceptionKey;
		break;
	case 0x58: // c
		this->keyAction = new RemoveAttributeKey;
		break;
	case 0x43: // v
		this->keyAction = new RemoveMethodKey;
		break;
	default:
		break;
	}
	return this->keyAction;
}
