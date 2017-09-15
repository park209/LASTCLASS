//Caret.cpp

#include "Caret.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include <afxwin.h>

Caret::Caret() {
	this->x = 0;
	this->y = 0;
	this->textEdit = 0;
}

Caret::Caret(Long x, Long y, TextEdit *textEdit) {
	this->x = x;
	this->y = y;
	this->textEdit = textEdit;
}

Caret::Caret(const Caret& source) {
	this->x = source.x;
	this->y = source.y;
	this->textEdit = source.textEdit;
}

Caret::~Caret() {

}

void Caret::MoveToIndex(Long characterIndex, Long rowIndex) {
	CPaintDC dc(this->textEdit);
	Long pointX = 5;
	Long pointY = rowIndex * this->textEdit->GetRowHeight() + 5;
	Long i = 0;

	while (i < characterIndex) {
		//pointX += dc.GetTabbedTextExtent(this->textEdit->text->GetAt(rowIndex)->GetAt(i)->MakeCString(), 0, 0).cx;
		i++;
	}
	this->textEdit->CreateSolidCaret(5, 20);
	if (this->textEdit->GetFlagBuffer() == 1) {
		this->textEdit->CreateSolidCaret(-20, 20);
	}
	this->textEdit->SetCaretPos(CPoint(pointX, pointY));
	this->textEdit->ShowCaret();
}

Caret& Caret::operator = (const Caret& source) {
	this->x = source.x;
	this->y = source.y;
	this->textEdit = source.textEdit;

	return *this;
}