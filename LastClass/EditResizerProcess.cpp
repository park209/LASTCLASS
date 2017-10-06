//EditResizerProcess.cpp

#include "EditResizerProcess.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Figure.h"
#include "FigureComposite.h"
#include "Diagram.h"
#include "Finder.h"
#include "Selection.h"
#include "Relation.h"
#include "FigureComposite.h"
#include "MemoBox.h"
#include "Class.h"
#include "ClassName.h"
#include "Template.h"

using namespace std;

EditResizerProcess::EditResizerProcess() {

}
EditResizerProcess::EditResizerProcess(const EditResizerProcess& source) {

}
EditResizerProcess::~EditResizerProcess() {

}
void EditResizerProcess::ResizeEditWidth(TextEdit *textEdit, CDC *cdc) {
	RECT rt;
	textEdit->GetClientRect(&rt);
	textEdit->SetWindowPos(&textEdit->wndTopMost, 0, 0,
		textEdit->text->MaxWidth(cdc) + CaretWidth, rt.bottom, SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOCOPYBITS);
}

void EditResizerProcess::ResizeEditHeight(TextEdit *textEdit, CDC *cdc) {
	RECT rt;
	textEdit->GetClientRect(&rt);
	textEdit->SetWindowPos(&textEdit->wndTopMost, 0, 0,
		rt.right, textEdit->GetRowHeight()*textEdit->text->GetLength(), SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOCOPYBITS);
}

void EditResizerProcess::ResizeEditAll(TextEdit *textEdit, CDC *cdc) {
	textEdit->SetWindowPos(&textEdit->wndTopMost, 0, 0,
		textEdit->text->MaxWidth(cdc) + CaretWidth, textEdit->GetRowHeight()*textEdit->text->GetLength() , SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOCOPYBITS);
}

void EditResizerProcess::RewindEdit(TextEdit *textEdit, CDC *cdc) {
	Long gabY_ = GabY * 2;
	if (dynamic_cast<MemoBox*>(textEdit->figure) || dynamic_cast<ClassName*>(textEdit->figure)) {
		gabY_ += MemoGab;
	}
	textEdit->SetWindowPos(&textEdit->wndTopMost,0, 0,
		textEdit->GetCriteriaWidth() - GabX *2, textEdit->GetCriteriaHeight() - gabY_, SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOCOPYBITS);
	if (dynamic_cast<Template*>(textEdit->figure)) {
		textEdit->SetWindowPos(&textEdit->wndTopMost,
			textEdit->GetCriteriaX()+GabX,
			textEdit->figure->GetY() + GabY,
			textEdit->GetCriteriaWidth() - GabX * 2,
			textEdit->GetCriteriaHeight() - gabY_,
			SWP_NOZORDER | SWP_NOREDRAW | SWP_NOCOPYBITS);
	}
}

void EditResizerProcess::ResizeClassWidth(TextEdit *textEdit) {
	RECT rt;
	textEdit->GetClientRect(&rt);
	ClassDiagramForm *classDiagramForm = (ClassDiagramForm*)textEdit->GetParentFrame();
	FigureComposite *object = static_cast<FigureComposite*>(classDiagramForm->selection->GetAt(0));
	Long distanceX;
	if (rt.right + GabX * 2 > textEdit->GetCriteriaWidth()) {
		distanceX = object->GetMinimumWidth() - object->GetWidth();
	}
	else {
		distanceX = textEdit->GetCriteriaWidth() - object->GetWidth();
	}
	object->ModifyComponetsToRightDirection(classDiagramForm->diagram, distanceX);
}

void EditResizerProcess::ResizeClassHeight(TextEdit *textEdit) {
	RECT rt;
	textEdit->GetClientRect(&rt);

	Long gabY_ = GabY * 2;
	if (dynamic_cast<MemoBox*>(textEdit->figure) || dynamic_cast<ClassName*>(textEdit->figure)) {
		gabY_ += MemoGab;
	}
	Long distanceY;
	if (rt.bottom + gabY_ > textEdit->GetCriteriaHeight()) {
		distanceY = rt.bottom + gabY_ - textEdit->figure->GetHeight();
	}
	else {
		distanceY = textEdit->GetCriteriaHeight() - textEdit->figure->GetHeight();
	}
	ClassDiagramForm *classDiagramForm = (ClassDiagramForm*)textEdit->GetParentFrame();
	FigureComposite *composite = static_cast<FigureComposite*>(classDiagramForm->selection->GetAt(0));

	Finder finder;
	Long quadrant;
	Long i = 0;
	Long startX = composite->GetX();
	Long startY = composite->GetY();
	Long endX = composite->GetX() + composite->GetWidth();
	Long endY = composite->GetY() + composite->GetHeight();
	SmartPointer<Figure*> iterator(classDiagramForm->diagram->CreateIterator());
	for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
		Long j = 0;
		FigureComposite *figureComposite = dynamic_cast<FigureComposite*>(iterator->Current());
		SmartPointer<Figure*> iterator_(figureComposite->CreateIterator());
		for (iterator_->First(); !iterator_->IsDone(); iterator_->Next()) {
			Figure *figure = iterator_->Current();
			if (dynamic_cast<Relation*>(iterator_->Current())) {
				Long relationEndX = figure->GetX() + figure->GetWidth();
				Long relationEndY = figure->GetY() + figure->GetHeight();
				if (startX <= relationEndX &&  relationEndX <= endX &&
					startY <= relationEndY &&  relationEndY <= endY) {
					quadrant = finder.FindQuadrant(relationEndX, relationEndY,
						startX, startY, endX, endY);
					if (quadrant == 3) {
						figure->EndPointMove(0, distanceY);
					}
				}
			}
		}
	}
	SmartPointer<Figure*> iterator__(composite->CreateIterator());
	for (iterator__->First(); !iterator__->IsDone(); iterator__->Next()) {
		if (iterator__->Current()->GetY() > textEdit->figure->GetY()) {
			iterator__->Current()->Move(0, distanceY);
		}
	}

	if (dynamic_cast<Class*>(composite)) {
		textEdit->figure->Modify(textEdit->figure->GetX(), textEdit->figure->GetY(), textEdit->figure->GetWidth(),
			textEdit->figure->GetHeight() + distanceY);
	}
	composite->Modify(composite->GetX(), composite->GetY(), composite->GetWidth(), composite->GetHeight() + distanceY);
}

void EditResizerProcess::ResizeEditWidthToLeft(TextEdit *textEdit, CDC *cdc) {
	RECT rt;
	textEdit->GetClientRect(&rt); //최대화 상태에서만 정상적인 rect를 출력. 최소화X
	
	textEdit->SetWindowPos(&textEdit->wndTopMost,
		textEdit->figure->GetX() + GabX - (textEdit->text->MaxWidth(cdc) - rt.right) - CaretWidth,
		textEdit->figure->GetY() + GabY,
		rt.right + (textEdit->text->MaxWidth(cdc) - rt.right) + CaretWidth,
		rt.bottom, SWP_NOZORDER | SWP_NOREDRAW | SWP_NOCOPYBITS);
}

void EditResizerProcess::ResizeTemplateWidth(TextEdit *textEdit) {
	//RECT rt;
	//textEdit->GetWindowRect(&rt);
	//
	//textEdit->figure->Modify(rt.left - GabX,
	//	textEdit->figure->GetY(),
	//	rt.right - rt.left + GabX*2,
	//	textEdit->figure->GetHeight());
	RECT rt;
	textEdit->GetClientRect(&rt);

	textEdit->figure->Modify(textEdit->figure->GetX() - (rt.right + GabX*2 + CaretWidth - textEdit->figure->GetWidth()),
		textEdit->figure->GetY(),
		rt.right + GabX*2 + CaretWidth,
		textEdit->figure->GetHeight());
}