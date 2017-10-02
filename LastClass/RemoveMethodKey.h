//RemoveMethodKey.h

#ifndef _REMOVEMETHODKEY_H
#define _REMOVEMETHODKEY_H

#include "KeyAction.h"

class ClassDiagramForm;
class TextEdit;
class RemoveMethodKey : public KeyAction {
public:
	RemoveMethodKey();
	RemoveMethodKey(const RemoveMethodKey& source);
	virtual ~RemoveMethodKey();

	void KeyPress(ClassDiagramForm *classDiagramForm);
	void KeyPress(TextEdit *textEdit);
};

#endif // _REMOVEMETHODKEY_H
