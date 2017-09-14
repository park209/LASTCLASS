//BackSpaceKey.h

#ifndef _BACKSPACEKEY_H
#define _BACKSPACEKEY_H

#include "KeyAction.h"

class TextEdit;
class BackSpaceKey : public KeyAction {
public:
	BackSpaceKey();
	BackSpaceKey(const BackSpaceKey& source);
	virtual ~BackSpaceKey();

	void KeyPress(TextEdit *textEdit);
};

#endif // _BACKSPACEKEY_H