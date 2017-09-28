//JKey.h

#ifndef _JKEY_H
#define _JKEY_H

#include "KeyAction.h"

class ClassDIagramForm;
class TextEdit;
class JKey : public KeyAction {
public:
	JKey();
	JKey(const JKey& source);
	virtual ~JKey();

	void KeyPress(ClassDiagramForm *classDiagramForm);
	void KeyPress(TextEdit *textEdit);
};

#endif // _JKEY_H
