//DeleteSelectedOne.h

#ifndef _DELETESELECTEDONE_H
#define _DELETESELECTEDONE_H

#include "KeyAction.h"

class ClassDIagramForm;
class TextEdit;
class DeleteSelectedOne : public KeyAction {
public:
	DeleteSelectedOne();
	DeleteSelectedOne(const DeleteSelectedOne& source);
	virtual ~DeleteSelectedOne();

	void KeyPress(ClassDiagramForm *classDiagramForm);
	void KeyPress(TextEdit *textEdit);
};

#endif // _DELETESELECTEDONE_H