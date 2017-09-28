//SKey.h

#ifndef _SKEY_H
#define _SKEY_H

#include "KeyAction.h"

class ClassDIagramForm;
class TextEdit;
class SKey : public KeyAction {
public:
	SKey();
	SKey(const SKey& source);
	virtual ~SKey();

	void KeyPress(ClassDiagramForm *classDiagramForm);
	void KeyPress(TextEdit *textEdit);
};

#endif // _SKEY_H