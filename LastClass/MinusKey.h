//MinusKey.h

#ifndef _MINUSKEY_H
#define _MINUSKEY_H

#include "KeyAction.h"

class TextEdit;
class  MinusKey : public KeyAction {
public:
	MinusKey();
	MinusKey(const MinusKey& source);
	virtual ~MinusKey();

	void KeyPress(TextEdit *textEdit);
};

#endif // _LEFTARROWKEY_H