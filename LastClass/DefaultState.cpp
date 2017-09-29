//DefaultState.cpp

#include "Diagram.h"
#include "Class.h"
#include "DefaultState.h"
#include "Finder.h"
#include "Selection.h"
#include "SelectionState.h"
#include "DrawingClass.h"
#include "DrawingMemoBox.h"
#include "DrawingGeneralization.h" 
#include "DrawingAggregation.h"
#include "DrawingAggregations.h"
#include "DrawingAssociation.h"
#include "DrawingComposition.h"
#include "DrawingCompositions.h"
#include "DrawingDependency.h"
#include "DrawingDirectedAssociation.h"
#include "DrawingMemoLine.h"
#include "DrawingRealization.h"
#include "MultipleSelectionState.h"
#include "DrawingRelationPoint.h"
#include "MovingRelation.h"
#include "MovingObject.h"
DefaultState* DefaultState::instance = 0;

MouseLButtonAction* DefaultState::Instance() {
	if (instance == 0) {
		instance = new DefaultState;
	}
	return instance;
}
void DefaultState::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

	Finder finder;
	CRect area(startX, startY, currentX, currentY);
	selection->DeleteAllItems();
	selection->SelectByArea(diagram, area);

	if (selection->GetLength() == 1) {
		this->ChangeState(mouseLButton, SelectionState::Instance());
	}
	if (selection->GetLength() > 1) {
		this->ChangeState(mouseLButton, MultipleSelectionState::Instance());
	}

}
void DefaultState::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	UINT object = mouseLButton->GetButtonState();
	if (object == 49) {
		this->ChangeState(mouseLButton, DrawingClass::Instance(), 49);
	}
	if (object == 81) {
		this->ChangeState(mouseLButton, DrawingMemoBox::Instance(), 101);
	}
	if (object == 50) {
		this->ChangeState(mouseLButton, DrawingGeneralization::Instance(), 50);
	}
	if (object == 55) {
		this->ChangeState(mouseLButton, DrawingAggregation::Instance(), 55);
	}
	if (object == 56) {
		this->ChangeState(mouseLButton, DrawingAggregations::Instance(), 56);
	}
	if (object == 53) {
		this->ChangeState(mouseLButton, DrawingAssociation::Instance(), 53);
	}
	if (object == 57) {
		this->ChangeState(mouseLButton, DrawingComposition::Instance(), 57);
	}
	if (object == 48) {
		this->ChangeState(mouseLButton, DrawingCompositions::Instance(), 48);
	}
	if (object == 52) {
		this->ChangeState(mouseLButton, DrawingDependency::Instance(), 52);
	}
	if (object == 54) {
		this->ChangeState(mouseLButton, DrawingDirectedAssociation::Instance(), 54);
	}
	if (object == 87) {
		this->ChangeState(mouseLButton, DrawingMemoLine::Instance(), 114);
	}
	if (object == 51) {
		this->ChangeState(mouseLButton, DrawingRealization::Instance(), 51);
	}
	if (mouseLButton->GetButtonState() == 0) {

		Long index = selection->SelectByPoint(startX, startY);
		if (index != -1 && selection->GetLength() > 1) {
			this->ChangeState(mouseLButton, MultipleSelectionState::Instance());
		}

		else {
			selection->DeleteAllItems();
			selection->SelectByPoint(diagram, startX, startY);
			if (selection->GetLength() == 1) {
				this->ChangeState(mouseLButton, SelectionState::Instance());
			}
		}
	}
}

void DefaultState::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPaintDC) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDC->SelectObject(&pen);
	cPaintDC->SetBkMode(TRANSPARENT);

	cPaintDC->MoveTo(startX, startY);
	cPaintDC->LineTo(currentX, startY);
	cPaintDC->MoveTo(startX, startY);
	cPaintDC->LineTo(startX, currentY);
	cPaintDC->MoveTo(currentX, startY);
	cPaintDC->LineTo(currentX, currentY);
	cPaintDC->MoveTo(startX, currentY);
	cPaintDC->LineTo(currentX, currentY);


	cPaintDC->SelectObject(oldPen);
	pen.DeleteObject();
}