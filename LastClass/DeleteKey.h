//DeleteKey.h

#ifndef _DELETEKEY_H
#define _DELETEKEY_H

#include "KeyAction.h"

class TextEdit;
class DeleteKey : public KeyAction {
public:
	DeleteKey();
	DeleteKey(const DeleteKey& source);
	virtual ~DeleteKey();

	void KeyPress(TextEdit *textEdit);
};

#endif // _DELETEKEY_H