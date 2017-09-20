//PlusKey.h

#ifndef _PLUSKEY_H
#define _PLUSKEY_H

#include "KeyAction.h"

class TextEdit;
class  PlusKey : public KeyAction {
public:
	PlusKey();
	PlusKey(const PlusKey& source);
	virtual ~PlusKey();

	void KeyPress(TextEdit *textEdit);
};

#endif // _LEFTARROWKEY_H