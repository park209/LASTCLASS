#ifndef _KEYACTION_H
#define _KEYACTION_H

class TextEdit;
class ClassDiagramForm;
class KeyAction {
public:
	KeyAction();
	virtual	~KeyAction() = 0;

	virtual void KeyPress(TextEdit *textEdit) = 0;
	virtual void KeyPress(ClassDiagramForm *classDiagramForm) = 0;
};

#endif //_KEYACTION_H