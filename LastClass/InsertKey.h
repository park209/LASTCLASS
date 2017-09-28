//InsertKey.h

#ifndef _INSERTKEY_H
#define _INSERTKEY_H

#include "KeyAction.h"

class TextEdit;
class ClassDiagramForm;
class InsertKey : public KeyAction {
public:
	InsertKey();
	InsertKey(const InsertKey& source);
	virtual ~InsertKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm);
};

#endif // _INSERTKEY_H