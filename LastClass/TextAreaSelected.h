//TextAreaSelected.h

#ifndef _TEXTAREASELECTED_H
#define _TEXTAREASELECTED_H

#include <afxwin.h>

typedef signed long int Long;

class TextEdit;
class TextAreaSelected {
public:
	TextAreaSelected();
	TextAreaSelected(const TextAreaSelected& source);
	~TextAreaSelected();

	void SelectTextArea(TextEdit *textEdit, CPaintDC *dc);

	Long GetStartCharacterIndex() const;
	Long GetStartRowIndex() const;
	Long GetEndCharacterIndex() const;
	Long GetEndRowIndex() const;
private:
	TextEdit *textEdit;
	Long startCharacterIndex;
	Long startRowIndex;
	Long endCharacterIndex;
	Long endRowIndex;
};

inline Long TextAreaSelected::GetStartCharacterIndex() const {
	return this->startCharacterIndex;
}
inline Long TextAreaSelected::GetStartRowIndex() const {
	return this->startRowIndex;
}
inline Long TextAreaSelected::GetEndCharacterIndex() const {
	return this->endCharacterIndex;
}
inline Long TextAreaSelected::GetEndRowIndex() const {
	return this->endRowIndex;
}


#endif // _TEXTAREASELECTED_H