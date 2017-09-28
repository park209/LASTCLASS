//FKey.h

#ifndef _FKEY_H
#define _FKEY_H

#include "KeyAction.h"

class ClassDiagramForm;
class TextEdit;
class FKey : public KeyAction {
public:
	FKey();
	FKey(const FKey& source);
	virtual ~FKey();

	void KeyPress(ClassDiagramForm *classDiagramForm);
	void KeyPress(TextEdit *textEdit);
};

#endif // _FKEY_H
