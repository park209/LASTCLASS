//DownArrowKey.h

#ifndef _DOWNARROWKEY_H
#define _DOWNARROWKEY_H

#include "KeyAction.h"

class TextEdit;
class DownArrowKey : public KeyAction {
public:
	DownArrowKey();
	DownArrowKey(const DownArrowKey& source);
	virtual ~DownArrowKey();

	void KeyPress(TextEdit *textEdit);
};

#endif // _DOWNARROWKEY_H