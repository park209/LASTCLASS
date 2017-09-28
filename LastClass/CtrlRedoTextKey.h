//CtrlRedoTextKey.h

#ifndef _CTRLREDOTEXTKEY_H
#define _CTRLREDOTEXTKEY_H

#include "KeyAction.h"

class TextEdit;
class ClassDiagramForm;
class CtrlRedoTextKey : public KeyAction {
public:
	CtrlRedoTextKey();
	CtrlRedoTextKey(const CtrlRedoTextKey& source);
	virtual ~CtrlRedoTextKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm);
};

#endif // _CTRLREDOTEXTKEY_H