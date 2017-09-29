//HKey.h

#ifndef _HKEY_H
#define _HKEY_H

#include "KeyAction.h"

class ClassDIagramForm;
class TextEdit;
class HKey : public KeyAction {
public:
	HKey();
	HKey(const HKey& source);
	virtual ~HKey();

	void KeyPress(ClassDiagramForm *classDiagramForm);
	void KeyPress(TextEdit *textEdit);
};

#endif // _HKEY_H
