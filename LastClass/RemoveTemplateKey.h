//RemoveTemplateKey.h

#ifndef _REMOVETEMPLATEKEY_H
#define _REMOVETEMPLATEKEY_H

#include "KeyAction.h"

class ClassDIagramForm;
class TextEdit;
class RemoveTemplateKey : public KeyAction {
public:
	RemoveTemplateKey();
	RemoveTemplateKey(const RemoveTemplateKey& source);
	virtual ~RemoveTemplateKey();

	void KeyPress(ClassDiagramForm *classDiagramForm);
	void KeyPress(TextEdit *textEdit);
};

#endif // _REMOVETEMPLATEKEY_H