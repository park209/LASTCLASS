//Caret.h

#ifndef _CARET_H
#define _CARET_H

#include "TextEdit.h"

typedef signed long int Long;

class Caret {
public:
	Caret();
	Caret(TextEdit *textEdit);
	Caret(const Caret& source);
	~Caret();

	void MoveToIndex(TextEdit *textEdit, CPaintDC *cPaintDc);

	Caret& operator = (const Caret& source);
private:
	TextEdit *textEdit;
};

#endif // _CARET_H