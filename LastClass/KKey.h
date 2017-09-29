//KKey.h

#ifndef _KKEY_H
#define _KKEY_H

#include "KeyAction.h"

class ClassDiagramForm;
class TextEdit;
class KKey : public KeyAction {
public:
	KKey();
	KKey(const KKey& source);
	virtual ~KKey();

	void KeyPress(ClassDiagramForm *classDiagramForm);
	void KeyPress(TextEdit *textEdit);
};

#endif // _KKEY_H
