//DKey.h

#ifndef _DKEY_H
#define _DKEY_H

#include "KeyAction.h"

class ClassDiagramForm;
class TextEdit;
class DKey : public KeyAction {
public:
	DKey();
	DKey(const DKey& source);
	virtual ~DKey();

	void KeyPress(ClassDiagramForm *classDiagramForm);
	void KeyPress(TextEdit *textEdit);
};

#endif // _DKEY_H
