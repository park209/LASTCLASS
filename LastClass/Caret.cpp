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
	Long pointX = 5;														//����
	Long pointY = this->rowIndex * textEdit->GetRowHeight() + 5;			//����
	Long i = 0;
	while (i < this->characterIndex) {
		pointX += dc->GetTabbedTextExtent(textEdit->text->GetAt(this->rowIndex)->GetAt(i)->MakeCString(), 0, 0).cx;
		i++;
	}

	textEdit->CreateSolidCaret(5, textEdit->GetRowHeight());
	if (textEdit->GetFlagBuffer() == 1) {
		textEdit->CreateSolidCaret(-20, 20);
	}
	this->currentCaretX = pointX;
	this->currentCaretY = pointY;
	textEdit->SetCaretPos(CPoint(pointX, pointY));
	textEdit->ShowCaret();
}

void Caret::MoveToPoint(TextEdit *textEdit, CPaintDC *cPaintDc, CPoint point) {
	Long x = point.x;
	Long y = point.y;

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
		width += cPaintDc->GetTabbedTextExtent(textEdit->text->GetAt(this->rowIndex)->GetAt(this->characterIndex)->MakeCString(), 0, 0).cx;
		this->characterIndex++; // -1 ���ϸ� ������
	}
	if (x > 5 && this->characterIndex > 0 &&
		x < width - (cPaintDc->GetTabbedTextExtent(textEdit->text->GetAt(this->rowIndex)->GetAt(this->characterIndex - 1)->MakeCString(), 0, 0).cx) / 2) {
		this->characterIndex--;
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

Caret& Caret::operator = (const Caret& source) {
	rowIndex = source.rowIndex;
	characterIndex = source.characterIndex;
	currentCaretX = source.currentCaretX;
	currentCaretY = source.currentCaretY;

	return *this;
}