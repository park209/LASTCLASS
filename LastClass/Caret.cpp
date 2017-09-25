//Caret.cpp

#include "Caret.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"

Caret::Caret() {
	rowIndex = 0;
	characterIndex = 0;
	currentCaretX = 0;
	currentCaretY = 0;
}

Caret::Caret(const Caret& source) {
	rowIndex = source.rowIndex;
	characterIndex = source.characterIndex;
	currentCaretX = source.currentCaretX;
	currentCaretY = source.currentCaretY;
}

Caret::~Caret() {

}


void Caret::MoveToIndex(TextEdit *textEdit, CPaintDC *dc) {
	Long pointX = 0;													//가로
	Long pointY = this->rowIndex * textEdit->GetRowHeight();			//세로
	pointX = textEdit->text->GetAt(this->rowIndex)->GetRowWidth(this->characterIndex, dc);
	textEdit->CreateSolidCaret(2, textEdit->GetRowHeight());
	if (textEdit->GetFlagBuffer() == 1) {
		textEdit->CreateSolidCaret(-dc->GetTextExtent(textEdit->text->GetAt(this->rowIndex)->GetAt(this->characterIndex-1)->MakeCString()).cx, textEdit->GetRowHeight());
	}
	this->currentCaretX = pointX;
	this->currentCaretY = pointY;
	textEdit->SetCaretPos(CPoint(pointX+5, pointY+5));
	textEdit->ShowCaret();
}

void Caret::MoveToPoint(TextEdit *textEdit, CPaintDC *dc, CPoint point) {
	Long x = point.x;
	Long y = point.y;
	CString str;
	this->rowIndex = 0;
	this->characterIndex = 0;

	Long height = 5;
	while (y > 5 && height <= y && this->rowIndex < textEdit->text->GetLength()) {
		height += textEdit->GetRowHeight();
		this->rowIndex++;
	}
	if (y > 5 && textEdit->text->GetLength() > 0) {
		this->rowIndex--;
	}
	Long width = 5;
	while (this->characterIndex < textEdit->text->GetAt(this->rowIndex)->GetLength() && x > 5 && width <= x) {
		str = textEdit->text->GetAt(this->rowIndex)->GetAt(this->characterIndex)->MakeCString();
		width += dc->GetTextExtent(str).cx;
		this->characterIndex++;
	}
	if (this->characterIndex > 0) {
		str = textEdit->text->GetAt(this->rowIndex)->GetAt(this->characterIndex - 1)->MakeCString();
		Long textWidth = dc->GetTextExtent(str).cx;
		if (x > 5 && x < width - textWidth / 2) {
			this->characterIndex--;
		}
	}
}

void Caret::MoveForwardRowIndex(Long index) {
	this->rowIndex += index;
}
void Caret::MoveBackwardRowIndex(Long index) {
	this->rowIndex -= index;
}
void Caret::MoveForwardCharacterIndex(Long index) {
	this->characterIndex += index;
}
void Caret::MoveBackwardCharacterIndex(Long index) {
	this->characterIndex -= index;
}
void Caret::SetCharacterIndex(Long index) {
	this->characterIndex = index;
}
void Caret::SetRowIndex(Long index) {
	this->rowIndex = index;
}

Caret& Caret::operator = (const Caret& source) {
	rowIndex = source.rowIndex;
	characterIndex = source.characterIndex;
	currentCaretX = source.currentCaretX;
	currentCaretY = source.currentCaretY;

	return *this;
}