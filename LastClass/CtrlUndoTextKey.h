//CtrlUndoTextKey.h

#ifndef _CTRLUNDOTEXTKEY_H
#define _CTRLUNDOTEXTKEY_H

#include "KeyAction.h"

class TextEdit;
class CtrlUndoTextKey : public KeyAction {
public:
	CtrlUndoTextKey();
	CtrlUndoTextKey(const CtrlUndoTextKey& source);
	virtual ~CtrlUndoTextKey();

	void KeyPress(TextEdit *textEdit);
};

#endif // _CTRLUNDOTEXTKEY_H