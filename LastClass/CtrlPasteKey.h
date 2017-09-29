#pragma once
//CtrlPasteKey.h

#ifndef _CTRLPASTEKEY_H
#define _CTRLPASTEKEY_H

#include "KeyAction.h"

class TextEdit;
class ClassDIagramForm;
class CtrlPasteKey : public KeyAction {
public:
	CtrlPasteKey();
	CtrlPasteKey(const CtrlPasteKey& source);
	virtual ~CtrlPasteKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm);
};

#endif // _CTRLPASTEKEY_H

