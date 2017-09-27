//CtrlCutKey.h

#ifndef _CTRLCUTKEY_H
#define _CTRLCUTKEY_H

#include "KeyAction.h"

class TextEdit;
class CtrlCutKey : public KeyAction {
public:
	CtrlCutKey();
	CtrlCutKey(const CtrlCutKey& source);
	virtual ~CtrlCutKey();

	void KeyPress(TextEdit *textEdit);
};

#endif // _CTRLCUTKEY_H

