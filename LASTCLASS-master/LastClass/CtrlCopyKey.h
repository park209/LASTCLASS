//CtrlCopyKey.h

#ifndef _CTRLCOPYKEY_H
#define _CTRLCOPYKEY_H

#include "KeyAction.h"

class TextEdit;
class CtrlCopyKey : public KeyAction {
public:
	CtrlCopyKey();
	CtrlCopyKey(const CtrlCopyKey& source);
	virtual ~CtrlCopyKey();

	void KeyPress(TextEdit *textEdit);
};

#endif // _CTRLCOPYKEY_H