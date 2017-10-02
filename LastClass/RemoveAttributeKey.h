//RemoveAttributeKey.h

#ifndef _REMOVEATTRIBUTEKEY_H
#define _REMOVEATTRIBUTEKEY_H

#include "KeyAction.h"

class ClassDIagramForm;
class TextEdit;
class RemoveAttributeKey : public KeyAction {
public:
	RemoveAttributeKey();
	RemoveAttributeKey(const RemoveAttributeKey& source);
	virtual ~RemoveAttributeKey();

	void KeyPress(ClassDiagramForm *classDiagramForm);
	void KeyPress(TextEdit *textEdit);
};

#endif // _REMOVEATTRIBUTEKEY_H
