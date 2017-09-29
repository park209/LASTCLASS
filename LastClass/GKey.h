//GKey.h

#ifndef _GKEY_H
#define _GKEY_H

#include "KeyAction.h"

class ClassDIagramForm;
class TextEdit;
class GKey : public KeyAction {
public:
	GKey();
	GKey(const GKey& source);
	virtual ~GKey();

	void KeyPress(ClassDiagramForm *classDiagramForm);
	void KeyPress(TextEdit *textEdit);
};

#endif // _GKEY_H