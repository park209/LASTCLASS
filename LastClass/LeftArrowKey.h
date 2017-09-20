//LeftArrowKey.h

#ifndef _LEFTARROWKEY_H
#define _LEFTARROWKEY_H

#include "KeyAction.h"

class TextEdit;
class LeftArrowKey : public KeyAction {
public:
	LeftArrowKey();
	LeftArrowKey(const LeftArrowKey& source);
	virtual ~LeftArrowKey();

	void KeyPress(TextEdit *textEdit);
};

#endif // _LEFTARROWKEY_H