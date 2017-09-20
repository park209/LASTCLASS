//UpArrowKey.h

#ifndef _UPARROWKEY_H
#define _UPARROWKEY_H

#include "KeyAction.h"

class TextEdit;
class UpArrowKey : public KeyAction {
public:
	UpArrowKey();
	UpArrowKey(const UpArrowKey& source);
	virtual ~UpArrowKey();

	void KeyPress(TextEdit *textEdit);
};

#endif // _UPARROWKEY_H