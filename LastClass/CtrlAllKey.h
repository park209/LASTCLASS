//CtrlAllKey.h

#ifndef _CTRLALLKEY_H
#define _CTRLALLKEY_H

#include "KeyAction.h"

class TextEdit;
class ClassDiagramForm;
class CtrlAllKey : public KeyAction {
public:
	CtrlAllKey();
	CtrlAllKey(const CtrlAllKey& source);
	virtual ~CtrlAllKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm);
};

#endif //_CTRLALLKEY_H