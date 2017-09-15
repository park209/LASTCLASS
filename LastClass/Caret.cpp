//Caret.cpp

#include "Caret.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"

Caret::Caret() {
	this->textEdit = 0;
}

Caret::Caret(TextEdit *textEdit) {
	this->textEdit = textEdit;
}

Caret::Caret(const Caret& source) {
	this->textEdit = source.textEdit;
}

Caret::~Caret() {

}

void Caret::MoveToIndex(TextEdit *textEdit, CPaintDC *dc) {
	Long pointX = 5;																//가로
	Long pointY = textEdit->GetRowIndex() * textEdit->GetRowHeight() + 5;			//세로
	Long i = 0;

	while (i < textEdit->GetCharacterIndex()) {
		pointX += dc->GetTabbedTextExtent(textEdit->text->GetAt(textEdit->GetRowIndex())->GetAt(i)->MakeCString(), 0, 0).cx;
		i++;
	}

	this->textEdit->CreateSolidCaret(5, textEdit->GetRowHeight());
	if (this->textEdit->GetFlagBuffer() == 1) {
		this->textEdit->CreateSolidCaret(-20, 20);
	}
	this->textEdit->SetCaretPos(CPoint(pointX, pointY));
	this->textEdit->ShowCaret();
}

Caret& Caret::operator = (const Caret& source) {
	this->textEdit = source.textEdit;

	return *this;
}