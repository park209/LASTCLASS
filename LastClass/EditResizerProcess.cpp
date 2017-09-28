//EditResizerProcess.cpp

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
#include "Relation.h"

EditResizerProcess::EditResizerProcess() {

}
EditResizerProcess::EditResizerProcess(const EditResizerProcess& source) {

}
EditResizerProcess::~EditResizerProcess() {

}
void EditResizerProcess::ResizeEditWidth(TextEdit *textEdit, CDC *cdc) {
	RECT rt;
	textEdit->GetClientRect(&rt);

	cdc->FillSolidRect(CRect(0, 0, textEdit->text->MaxWidth(cdc) + textEdit->rowHeight, 
																	textEdit->figure->GetHeight()), RGB(255, 255, 255));

	textEdit->MoveWindow(textEdit->figure->GetX(), textEdit->figure->GetY(),
		textEdit->text->MaxWidth(cdc) + 9, textEdit->figure->GetHeight());
}

void EditResizerProcess::ResizeEditHeight(TextEdit *textEdit, CDC *cdc) {
	RECT rt;
	textEdit->GetClientRect(&rt);

	cdc->FillSolidRect(CRect(0, 0, textEdit->figure->GetWidth() + 5,
		textEdit->GetRowHeight()*textEdit->text->GetLength()+5), RGB(255, 255, 255));

	textEdit->MoveWindow(textEdit->figure->GetX(), textEdit->figure->GetY(),
		textEdit->figure->GetWidth(), textEdit->GetRowHeight()*textEdit->text->GetLength() + 10);
}

void EditResizerProcess::ResizeEditAll(TextEdit *textEdit, CDC *cdc) {
	RECT rt;
	textEdit->GetClientRect(&rt);

	cdc->FillSolidRect(CRect(0, 0, textEdit->text->MaxWidth(cdc) + textEdit->rowHeight,
									textEdit->GetRowHeight()*textEdit->text->GetLength()), RGB(255, 255, 255));

	textEdit->MoveWindow(textEdit->figure->GetX(), textEdit->figure->GetY(),
		textEdit->text->MaxWidth(cdc) + 9, textEdit->GetRowHeight()*textEdit->text->GetLength() + 5);
}

void EditResizerProcess::RewindEdit(TextEdit *textEdit, CDC *cdc) {
	RECT rt;
	textEdit->GetClientRect(&rt);
	cdc->FillSolidRect(CRect(0, 0, textEdit->figure->GetWidth() + 5, textEdit->figure->GetHeight()), RGB(255, 255, 255));

	textEdit->MoveWindow(textEdit->figure->GetX(), textEdit->figure->GetY(),
		textEdit->figure->GetWidth(), textEdit->figure->GetHeight());
}

void EditResizerProcess::ResizeClassWidth(TextEdit *textEdit, CDC *cdc) {
	RECT rt;
	textEdit->GetClientRect(&rt);

	textEdit->figure->SetMinimumWidth(rt.right);
	ClassDiagramForm *classDiagramForm = (ClassDiagramForm*)textEdit->GetParentFrame();
	Long width = classDiagramForm->selection->GetAt(0)->GetWidth();
	if (textEdit->figure->GetMinimumWidth() > width) {
		static_cast<FigureComposite*>(classDiagramForm->selection->GetAt(0))->
			ModifyComponetsToRightDirection(classDiagramForm->diagram, textEdit->figure->GetMinimumWidth() - width + 9);
		static_cast<Class*>(classDiagramForm->selection->GetAt(0))->SetMinimumWidth();
	}
	textEdit->ReleaseDC(cdc);
}

void EditResizerProcess::ResizeClassHeight(TextEdit *textEdit) {
	CDC * cdc = textEdit->GetDC();
	RECT rt;
	textEdit->GetClientRect(&rt);

	Long distanceY = rt.bottom - textEdit->figure->GetHeight();

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
	textEdit->figure->Modify(textEdit->figure->GetX(), textEdit->figure->GetY(), textEdit->figure->GetWidth(), 
		textEdit->figure->GetHeight() + distanceY);
	composite->Modify(composite->GetX(), composite->GetY(), composite->GetWidth(), composite->GetHeight() + distanceY);
}