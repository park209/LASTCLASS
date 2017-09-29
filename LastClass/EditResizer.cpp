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
#include "MemoBox.h"

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
	Long gabY_ = GabY*2;
	if (dynamic_cast<MemoBox*>(textEdit->figure)) {
		gabY_ += MemoGab;
	}

	if (textEdit->text->MaxWidth(cdc) + GabX * 2  > textEdit->GetCriteriaWidth()) {			//�۳ʺ� Ŭ������ �Ѿ�µ�
		if (textEdit->GetRowHeight()*textEdit->text->GetLength() + gabY_ > textEdit->GetCriteriaHeight()) {
			resizer.ResizeEditAll(textEdit, cdc);											//�۳��̰� Ŭ������ �Ѿ�� �Ѵ�O
		}
		else {																				//�۳��̰� Ŭ������ �ȳѾ�� �ʺ�
			resizer.ResizeEditWidth(textEdit, cdc);
		}
	}																						//�۳ʺ� Ŭ������ �ȳѾ�µ�
	else if (textEdit->GetRowHeight()*textEdit->text->GetLength() + gabY_ > textEdit->GetCriteriaHeight()) {
		resizer.ResizeEditHeight(textEdit, cdc);
	}
	else {																					//�۳��̰� Ŭ������ �Ѿ�� �Ѵ�X
		resizer.RewindEdit(textEdit, cdc);
	}
}

void EditResizer::ResizeClass(TextEdit *textEdit, CDC *cdc) {
	EditResizerProcess resizer;
	RECT rt;
	textEdit->GetClientRect(&rt);
	ClassDiagramForm *classDiagramForm = (ClassDiagramForm*)textEdit->GetParentFrame();
	Long gabY_ = GabY * 2;

	if(dynamic_cast<Class*>(classDiagramForm->selection->GetAt(0))){
		textEdit->figure->SetMinimumWidth(textEdit->text->MaxWidth(cdc) + GabX * 2);
		static_cast<Class*>(classDiagramForm->selection->GetAt(0))->SetMinimumWidth();
	}
	else {
		gabY_ += MemoGab;
		if (textEdit->text->MaxWidth(cdc) + GabX * 2 > 120) {
			textEdit->figure->SetMinimumWidth(textEdit->text->MaxWidth(cdc) + GabX * 2);
		}
	}

	textEdit->figure->SetMinimumHeight(textEdit->GetRowHeight()*textEdit->text->GetLength() + gabY_);

	if (rt.right + GabX*2 > textEdit->GetCriteriaWidth() ) {
		resizer.ResizeClassWidth(textEdit,cdc);
	}
	if (rt.bottom + gabY_ > textEdit->GetCriteriaHeight()) {
		resizer.ResizeClassHeight(textEdit);
	}
}