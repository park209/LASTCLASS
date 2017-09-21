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
	Long pointX = 5;														//가로
	Long pointY = this->rowIndex * textEdit->GetRowHeight() + 5;			//세로
	CString str;
	Long i = 0;
	while (i < this->characterIndex) {
		str = textEdit->text->GetAt(this->rowIndex)->GetAt(i)->MakeCString();
		if (str == "\t") {
			str = "    ";
		}
		pointX += dc->GetTextExtent(str).cx;
		i++;
	}
	textEdit->CreateSolidCaret(2, textEdit->GetRowHeight());
	if (textEdit->GetFlagBuffer() == 1) {
		textEdit->CreateSolidCaret(-dc->GetTextExtent(textEdit->text->GetAt(this->rowIndex)->GetAt(this->characterIndex-1)->MakeCString()).cx, textEdit->GetRowHeight());
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
	while (x > 5 && width < x && this->characterIndex < textEdit->text->GetAt(this->rowIndex)->GetLength()) {
		str = textEdit->text->GetAt(this->rowIndex)->GetAt(this->characterIndex)->MakeCString();
		if (str == "\t") {
			str = "    ";
		}
		width += cPaintDc->GetTextExtent(str).cx;
		this->characterIndex++; // -1 안하면 다음꺼
	}
	if (this->characterIndex > 0) {
		str = textEdit->text->GetAt(this->rowIndex)->GetAt(this->characterIndex - 1)->MakeCString();
		if (str == "\t") {
			str = "    ";
		}
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