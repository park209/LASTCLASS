//HomeKey.h

#ifndef _HOMEKEY_H
#define _HOMEKEY_H

#include "KeyAction.h"

class TextEdit;
class CLassDiagramForam;
class HomeKey : public KeyAction {
public:
	HomeKey();
	HomeKey(const HomeKey& source);
	virtual ~HomeKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm);
};

#endif // _HOMEKEY_H