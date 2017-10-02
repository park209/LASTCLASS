//DeleteGraphicKey.h

#ifndef _DELETEGRAPHICKEY_H
#define _DELETEGRAPHICKEY_H

#include "KeyAction.h"

class ClassDIagramForm;
class TextEdit;
class DeleteGraphicKey : public KeyAction {
public:
	DeleteGraphicKey();
	DeleteGraphicKey(const DeleteGraphicKey& source);
	virtual ~DeleteGraphicKey();

	void KeyPress(ClassDiagramForm *classDiagramForm);
	void KeyPress(TextEdit *textEdit);
};

#endif // _DELETEGRAPHICKEY_H