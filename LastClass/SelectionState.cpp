//SelectionState.cpp
#include "MovingLine.h"
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
#include "MultipleSelectionState.h"
#include "SelfRelation.h"
#include "MovingSelfRelation.h"
SelectionState* SelectionState::instance = 0;

MouseLButtonAction* SelectionState::Instance() {
	if (instance == 0) {
		instance = new SelectionState;
	}
	return instance;
}
void SelectionState::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
}

void SelectionState::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	UINT object = mouseLButton->GetButtonState();
	if (object == 49) {
		this->ChangeState(mouseLButton, DrawingClass::Instance(), 49);
	}
	else if (object == 101) {
		this->ChangeState(mouseLButton, DrawingMemoBox::Instance(), 101);
	}
	else if (object == 50) {
		this->ChangeState(mouseLButton, DrawingGeneralization::Instance(), 50);
	}
	else if (object == 55) {
		this->ChangeState(mouseLButton, DrawingAggregation::Instance(), 55);
	}
	else if (object == 56) {
		this->ChangeState(mouseLButton, DrawingAggregations::Instance(), 56);
	}
	else if (object == 53) {
		this->ChangeState(mouseLButton, DrawingAssociation::Instance(), 53);
	}
	else if (object == 57) {
		this->ChangeState(mouseLButton, DrawingComposition::Instance(), 57);
	}
	else if (object == 113) {
		this->ChangeState(mouseLButton, DrawingCompositions::Instance(), 113);
	}
	else if (object == 52) {
		this->ChangeState(mouseLButton, DrawingDependency::Instance(), 52);
	}
	else if (object == 54) {
		this->ChangeState(mouseLButton, DrawingDirectedAssociation::Instance(), 54);
	}
	else if (object == 114) {
		this->ChangeState(mouseLButton, DrawingMemoLine::Instance(), 114);
	}
	else if (object == 51) {
		this->ChangeState(mouseLButton, DrawingRealization::Instance(), 51);
	}
	else if (object == 87) {
		this->ChangeState(mouseLButton, DrawingMemoLine::Instance(), 87);
	}
	if (GetKeyState(VK_SHIFT) >= 0) {
		Long index = selection->SelectByPoint(startX, startY);
		if (index == 3) { // 크기조절
			this->ChangeState(mouseLButton, DrawingResizing::Instance());
		}
		if (index == 5) { // 내부 선이동
			this->ChangeState(mouseLButton, MovingLine::Instance());
		}
		if (index == 6) {
			this->ChangeState(mouseLButton, MovingSelfRelation::Instance());
		}
		if (index == -1) {
			selection->DeleteAllItems();
			selection->SelectByPoint(diagram, startX, startY);
			if (selection->GetLength() == 0) {
				this->ChangeDefault(mouseLButton);
			}
		}
	}
	else if (GetKeyState(VK_SHIFT) < 0) {
		selection->SelectByPoint(diagram, startX, startY);
		this->ChangeState(mouseLButton, MultipleSelectionState::Instance());
	}
}
void SelectionState::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {
	if (startX != currentX && startY != currentY) {
		Long index = selection->SelectByPoint(startX, startY);
		if (dynamic_cast<SelfRelation*>(selection->GetAt(0))) {
			index = 6;
			}


		if (index == 1) { // 끝점이동
			this->ChangeState(mouseLButton, MovingRelation::Instance());
		}
		if (index == 2) { // 선분리
			this->ChangeState(mouseLButton, DrawingRelationPoint::Instance());
		}
		
		if (index == 4 || index ==3 || index== 5) { // 기호 이동
			this->ChangeState(mouseLButton, MovingObject::Instance());
		}
		if (index == 6) {
			this->ChangeState(mouseLButton, MovingSelfRelation::Instance());
		}
		if (index == -1) {
			this->ChangeDefault(mouseLButton);
		}
		
	}

}