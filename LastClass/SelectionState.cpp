
#include "Diagram.h"
#include "Class.h"
#include "SelectionState.h"
#include "DrawingClass.h"
#include "DrawingRelation.h"
#include "DefaultState.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "Figure.h"
#include "Finder.h"
#include "Selection.h"
#include "MovingObject.h"

SelectionState* SelectionState::instance = 0;

MouseLButtonAction* SelectionState::Instance() {
	if (instance == 0) {
		instance = new SelectionState;
	}
	return instance;
}
void SelectionState::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){
	
}
void SelectionState::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){
	selection->DeleteAllItems();
	selection->SelectByPoint(diagram, currentX, currentY);
	if (selection->GetLength() == 0) {
		this->ChangeDefault(mouseLButton);
	}
}
void SelectionState::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPaintDC) {


	if (mouseLButton->GetButtonState() == 50) {
		this->ChangeState(mouseLButton, DrawingRelation::Instance(), 50);
	}

		if (selection->GetLength() == 1) {
			this->ChangeState(mouseLButton, MovingObject::Instance());

	}
}