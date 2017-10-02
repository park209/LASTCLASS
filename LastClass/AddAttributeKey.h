//AddAttributeKey.h

#ifndef _ADDATTRIBUTEKEY_H
#define _ADDATTRIBUTEKEY_H

#include "KeyAction.h"

class ClassDIagramForm;
class TextEdit;
class AddAttributeKey : public KeyAction {
public:
	AddAttributeKey();
	AddAttributeKey(const AddAttributeKey& source);
	virtual ~AddAttributeKey();

	void KeyPress(ClassDiagramForm *classDiagramForm);
	void KeyPress(TextEdit *textEdit);
};

#endif // _ADDATTRIBUTEKEY_H