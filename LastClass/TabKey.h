//TabKey.h

#ifndef _TABKEY_H
#define _TABKEY_H

#include "KeyAction.h"

class TextEdit;
class TabKey : public KeyAction {
public:
	TabKey();
	TabKey(const TabKey& source);
	virtual ~TabKey();

	void KeyPress(TextEdit *textEdit);
};

#endif // _TABKEY_H