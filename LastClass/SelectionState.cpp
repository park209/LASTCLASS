//SelectionState.cpp

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
#include "MovingObject.h"
#include "MovingRelation.h"
#include "DrawingRelationPoint.h"
#include "DrawingResizing.h"
#include "MovingLine.h"

SelectionState* SelectionState::instance = 0;

MouseLButtonAction* SelectionState::Instance() {
	if (instance == 0) {
		instance = new SelectionState;
	}
	return instance;
}
void SelectionState::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
}

void SelectionState::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	Long index;
	UINT object = mouseLButton->GetButtonState();
	if (object == 49) {
		this->ChangeState(mouseLButton, DrawingClass::Instance(), 49);
	}
	if (object == 101) {
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
	if (object == 113) {
		this->ChangeState(mouseLButton, DrawingCompositions::Instance(), 113);
	}
	if (object == 52) {
		this->ChangeState(mouseLButton, DrawingDependency::Instance(), 52);
	}
	if (object == 54) {
		this->ChangeState(mouseLButton, DrawingDirectedAssociation::Instance(), 54);
	}
	if (object == 114) {
		this->ChangeState(mouseLButton, DrawingMemoLine::Instance(), 114);
	}
	if (object == 51) {
		this->ChangeState(mouseLButton, DrawingRealization::Instance(), 51);
	}
	index = selection->SelectByPoint(currentX, currentY);
	if (index == -1) {
		selection->DeleteAllItems();
		selection->SelectByPoint(diagram, currentX, currentY);
	}
	if (selection->GetLength() == 0) {
		this->ChangeDefault(mouseLButton);
	}
}

void SelectionState::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPaintDC) {
	Long index = selection->SelectByPoint(currentX, currentY);
	if (index == 1) {
		this->ChangeState(mouseLButton, MovingRelation::Instance());
	}
	if (index == 2) {
		this->ChangeState(mouseLButton, DrawingRelationPoint::Instance());
	}
	if (index == 3) {
		this->ChangeState(mouseLButton, DrawingResizing::Instance());
	}
	if (index == 4) {
		this->ChangeState(mouseLButton, MovingObject::Instance());
	}
	if (index == 5) {
		this->ChangeState(mouseLButton, MovingLine::Instance());
	}
}