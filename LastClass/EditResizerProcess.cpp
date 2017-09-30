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
	textEdit->SetWindowPos(&textEdit->wndTop, 0, 0,
		textEdit->text->MaxWidth(cdc) , rt.bottom, SWP_FRAMECHANGED | SWP_NOMOVE);
}

void EditResizerProcess::ResizeEditHeight(TextEdit *textEdit, CDC *cdc) {
	RECT rt;
	textEdit->GetClientRect(&rt);
	textEdit->SetWindowPos(&textEdit->wndTop, 0, 0,
		rt.right, textEdit->GetRowHeight()*textEdit->text->GetLength(), SWP_FRAMECHANGED | SWP_NOMOVE);
}

void EditResizerProcess::ResizeEditAll(TextEdit *textEdit, CDC *cdc) {
	textEdit->SetWindowPos(&textEdit->wndTop, 0, 0,
		textEdit->text->MaxWidth(cdc), textEdit->GetRowHeight()*textEdit->text->GetLength() , SWP_FRAMECHANGED | SWP_NOMOVE);
}

void EditResizerProcess::RewindEdit(TextEdit *textEdit, CDC *cdc) {
	Long gabY_ = GabY * 2;
	if (dynamic_cast<MemoBox*>(textEdit->figure)) {
		gabY_ += MemoGab;
	}
	textEdit->SetWindowPos(&textEdit->wndTop,0, 0,
		textEdit->GetCriteriaWidth() - GabX *2, textEdit->GetCriteriaHeight() - gabY_, SWP_FRAMECHANGED | SWP_NOMOVE);
}

void EditResizerProcess::ResizeClassWidth(TextEdit *textEdit, CDC *cdc) {
	RECT rt;
	textEdit->GetClientRect(&rt);

	ClassDiagramForm *classDiagramForm = (ClassDiagramForm*)textEdit->GetParentFrame();
	FigureComposite *object = static_cast<FigureComposite*>(classDiagramForm->selection->GetAt(0));

	Long distanceX = object->GetMinimumWidth() - object->GetWidth();
	
	object->ModifyComponetsToRightDirection(classDiagramForm->diagram, distanceX);
}

void EditResizerProcess::ResizeClassHeight(TextEdit *textEdit) {
	CDC * cdc = textEdit->GetDC();
	RECT rt;
	textEdit->GetClientRect(&rt);
	
	Long gabY_ = GabY * 2;
	if (dynamic_cast<MemoBox*>(textEdit->figure)) {
		gabY_ += MemoGab;
	}

	Long distanceY = rt.bottom + gabY_ - textEdit->figure->GetHeight();

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
	for(iterator->First();!iterator->IsDone();iterator->Next()){
		Long j = 0;
		FigureComposite *figureComposite = dynamic_cast<FigureComposite*>(iterator->Current());
		SmartPointer<Figure*> iterator_(figureComposite->CreateIterator());
		for (iterator_->First();!iterator_->IsDone();iterator_->Next()) {
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
	for (iterator__->First();!iterator__->IsDone();iterator__->Next()) {
		if (iterator__->Current()->GetY() > textEdit->figure->GetY()) {
			iterator__->Current()->Move(0, distanceY);
		}
	}

	if (dynamic_cast<Class*>(composite)) {
		textEdit->figure->Modify(textEdit->figure->GetX(), textEdit->figure->GetY(), textEdit->figure->GetWidth(),
			textEdit->figure->GetHeight() + distanceY);
	}
	composite->Modify(composite->GetX(), composite->GetY(), composite->GetWidth(), composite->GetHeight() + distanceY);

	textEdit->ReleaseDC(cdc);
}