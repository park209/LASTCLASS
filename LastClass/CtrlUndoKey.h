//CtrlUndoKey.h

#ifndef _CTRLUNDOKEY_H
#define _CTRLUNDOKEY_H

#include "KeyAction.h"

class TextEdit;
class CtrlUndoKey : public KeyAction {
public:
	CtrlUndoKey();
	CtrlUndoKey(const CtrlUndoKey& source);
	virtual ~CtrlUndoKey();

	void KeyPress(TextEdit *textEdit);
};

#endif // _CTRLUNDOKEY_H