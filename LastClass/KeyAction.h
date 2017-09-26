#ifndef _KEYACTION_H
#define _KEYACTION_H

class TextEdit;
class KeyAction {
public:
	KeyAction();
	virtual	~KeyAction();

	virtual void KeyPress(TextEdit *textEdit) = 0;
};

#endif //_KEYACTION_H