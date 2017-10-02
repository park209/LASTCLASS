//RemoveReceptionKey.h

#ifndef _REMOVERECEPTIONKEY_H
#define _REMOVERECEPTIONKEY_H

#include "KeyAction.h"

class ClassDiagramForm;
class TextEdit;
class RemoveReceptionKey : public KeyAction {
public:
	RemoveReceptionKey();
	RemoveReceptionKey(const RemoveReceptionKey& source);
	virtual ~RemoveReceptionKey();

	void KeyPress(ClassDiagramForm *classDiagramForm);
	void KeyPress(TextEdit *textEdit);
};

#endif // _REMOVERECEPTIONKEY_H
