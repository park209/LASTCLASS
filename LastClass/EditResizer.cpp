//EditResizer.cpp

#include "EditResizer.h"
#include "EditResizerProcess.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Figure.h"
#include "FigureComposite.h"
#include "Diagram.h"
#include "Class.h"
#include "Finder.h"
#include "Selection.h"

EditResizer::EditResizer() {

}
EditResizer::EditResizer(const EditResizer& source) {

}
EditResizer::~EditResizer() {

}

void EditResizer::ResizeEdit(TextEdit *textEdit, CDC *cdc) {
	EditResizerProcess resizer;
	RECT rt;
	textEdit->GetClientRect(&rt);

	if (textEdit->text->MaxWidth(cdc) + 9 > textEdit->figure->GetWidth()) {				//글너비가 클래스를 넘어가는데
		if (textEdit->GetRowHeight()*textEdit->text->GetLength() > textEdit->figure->GetHeight()) {
			resizer.ResizeEditAll(textEdit, cdc);										//글높이가 클래스를 넘어가면 둘다O
		}
		else {																			//글높이가 클래스를 안넘어가면 너비만
			resizer.ResizeEditWidth(textEdit, cdc);
		}
	}
	else if (textEdit->text->MaxWidth(cdc) + 9 <= textEdit->figure->GetWidth()) {		//글너비가 클래스를 안넘어가는데

		if (textEdit->GetRowHeight()*textEdit->text->GetLength() > textEdit->figure->GetHeight()) {
			resizer.ResizeEditHeight(textEdit, cdc);									//글높이가 클래스를 넘어가면 높이만
		}
		else {																			//글높이가 클래스를 넘어가면 둘다X
			resizer.RewindEdit(textEdit, cdc);
		}
	}
}

void EditResizer::ResizeClass(TextEdit *textEdit, CDC *cdc) {
	EditResizerProcess resizer;
	if (textEdit->text->MaxWidth(cdc) + 9 > textEdit->figure->GetWidth()) {
		resizer.ResizeClassWidth(textEdit,cdc);
	}
	if (textEdit->GetRowHeight()*textEdit->text->GetLength() > textEdit->figure->GetHeight()) {
		resizer.ResizeClassHeight(textEdit);
	}
}
