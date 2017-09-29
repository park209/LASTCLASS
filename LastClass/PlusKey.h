//PlusKey.h

#ifndef _PLUSKEY_H
#define _PLUSKEY_H

#include "KeyAction.h"

class TextEdit;
class ClassDiagramForm;
class  PlusKey : public KeyAction {
public:
	PlusKey();
	PlusKey(const PlusKey& source);
	virtual ~PlusKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm);
};

#endif // _LEFTARROWKEY_H