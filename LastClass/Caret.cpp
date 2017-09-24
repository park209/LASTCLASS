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
	Long pointX = 5;                                          //°¡·Î
	Long pointY = this->rowIndex * textEdit->GetRowHeight() + 5;         //¼¼·Î
	Long j;
	CString str;
	Long column = 0;
	Long tabWidth = 0;
	Long i = 0;
	while (i < this->characterIndex) {
		str = textEdit->text->GetAt(this->rowIndex)->GetAt(i)->MakeCString();
		if (str.GetAt(0) & 0x80) { // 2¹ÙÀÌÆ®¹®ÀÚ¸é 2Ä­
			column += 2;
		}
		else if (str == "        ") { // ÅÇ¹®ÀÚ¸é ÀÌÀü¹®ÀÚÀÇ Ä­À» ¼À
			tabWidth = (column + 8) / 8 * 8 - column;
			column += tabWidth;
			j = 0;
			str = "";
			while (j < tabWidth) { //±¸ÇÑ Ä­¸¸Å­ ÅÇ¹®ÀÚÀÇ Å©±â¸¦ Á¤ÇÔ
				str += " ";
				j++;
			}
		}
		else { // 1¹ÙÀÌÆ®¹®ÀÚ¸é 1Ä­
			column += 1;
		}
		pointX += dc->GetTextExtent(str).cx;
		i++;
	}
	textEdit->CreateSolidCaret(2, textEdit->GetRowHeight());
	if (textEdit->GetFlagBuffer() == 1) {
		textEdit->CreateSolidCaret(-dc->GetTextExtent(textEdit->text->GetAt(this->rowIndex)->GetAt(this->characterIndex - 1)->MakeCString()).cx, textEdit->GetRowHeight());
	}
	this->currentCaretX = pointX;
	this->currentCaretY = pointY;
	textEdit->SetCaretPos(CPoint(pointX, pointY));
	textEdit->ShowCaret();
}

void Caret::MoveToPoint(TextEdit *textEdit, CPaintDC *cPaintDc, CPoint point) {
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
		width += cPaintDc->GetTextExtent(str).cx;
		this->characterIndex++; // -1 ¾ÈÇÏ¸é ´ÙÀ½²¨
	}
	if (this->characterIndex > 0) {
		str = textEdit->text->GetAt(this->rowIndex)->GetAt(this->characterIndex - 1)->MakeCString();
		Long textWidth = cPaintDc->GetTextExtent(str).cx;
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