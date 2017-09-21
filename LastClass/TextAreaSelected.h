//TextAreaSelected.h

#ifndef _TEXTAREASELECTED_H
#define _TEXTAREASELECTED_H

#include <afxwin.h>

class TextEdit;
class TextAreaSelected {
public:
	TextAreaSelected();
	TextAreaSelected(const TextAreaSelected& source);
	~TextAreaSelected();

	void SelectTextArea(TextEdit *textEdit, CPaintDC *dc);
private:
	TextEdit *textEdit;
};

#endif _TEXTAREASELECTED_H