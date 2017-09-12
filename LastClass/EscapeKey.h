//EscapeKey.h

#ifndef _ESCAPEKEY_H
#define _ESCAPEKEY_H

#include "KeyAction.h"

class TextEdit;
class EscapeKey : public KeyAction {
public:
	EscapeKey();
	EscapeKey(const EscapeKey& source);
	virtual ~EscapeKey();

	void KeyPress(TextEdit *textEdit);
};

#endif // _ESCAPEKEY_H