//AddMethodKey.h

#ifndef _ADDMETHODKEY_H
#define _ADDMETHODKEY_H

#include "KeyAction.h"

class ClassDIagramForm;
class TextEdit;
class AddMethodKey : public KeyAction {
public:
	AddMethodKey();
	AddMethodKey(const AddMethodKey& source);
	virtual ~AddMethodKey();

	void KeyPress(ClassDiagramForm *classDiagramForm);
	void KeyPress(TextEdit *textEdit);
};

#endif // _ADDMETHODKEY_H
