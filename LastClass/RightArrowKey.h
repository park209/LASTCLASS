//RightArrowKey.h

#ifndef _RIGHTARROWKEY_H
#define _RIGHTARROWKEY_H

#include "KeyAction.h"

class TextEdit;
class ClassDiagramForm;
class RightArrowKey : public KeyAction {
public:
	RightArrowKey();
	RightArrowKey(const RightArrowKey& source);
	virtual ~RightArrowKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm);
};

#endif // _RIGHTARROWKEY_H