//EndKey.h

#ifndef _ENDKEY_H
#define _ENDKEY_H

#include "KeyAction.h"

class TextEdit;
class EndKey : public KeyAction {
public:
	EndKey();
	EndKey(const EndKey& source);
	virtual ~EndKey();

	void KeyPress(TextEdit *textEdit);
};

#endif // _ENDKEY_H