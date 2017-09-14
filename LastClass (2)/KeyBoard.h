//KeyBoard.h

#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <afxwin.h>

class KeyAction;
class TextEdit;
class KeyBoard {
public:
	KeyBoard();
	KeyBoard(const KeyBoard& source);
	~KeyBoard();
	KeyBoard& operator = (const KeyBoard& source);
	void KeyDown(TextEdit *textEdit, UINT nChar, UINT nRepCnt, UINT nFlags);
public:
	KeyAction *keyAction;
};

#endif // _KEYBOARD_H