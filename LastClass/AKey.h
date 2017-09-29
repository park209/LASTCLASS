//AKey.h

#ifndef _AKEY_H
#define _AKEY_H

#include "KeyAction.h"

class ClassDIagramForm;
class TextEdit;
class AKey : public KeyAction {
public:
	AKey();
	AKey(const AKey& source);
	virtual ~AKey();

	virtual void KeyPress(ClassDiagramForm *classDiagramForm);
	virtual void KeyPress(TextEdit *textEdit);
};

#endif // _AKEY_H