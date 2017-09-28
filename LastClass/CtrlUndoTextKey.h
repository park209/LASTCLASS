//CtrlUndoTextKey.h

#ifndef _CTRLUNDOTEXTKEY_H
#define _CTRLUNDOTEXTKEY_H

#include "KeyAction.h"

class TextEdit;
class ClassDiagramForm;
class CtrlUndoTextKey : public KeyAction {
public:
	CtrlUndoTextKey();
	CtrlUndoTextKey(const CtrlUndoTextKey& source);
	virtual ~CtrlUndoTextKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm);
};

#endif // _CTRLUNDOTEXTKEY_H