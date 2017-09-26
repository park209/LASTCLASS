#include "MultipleSelectionState.h"
#include "Selection.h"
#include "Relation.h"
#include "MovingVisitor.h"

MultipleSelectionState* MultipleSelectionState::instance = 0;

MouseLButtonAction* MultipleSelectionState::Instance() {
	if (instance == 0) {
		instance = new MultipleSelectionState;
	}
	return instance;
}

void MultipleSelectionState::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	Long distanceX = currentX - startX;
	Long distanceY = currentY - startY;
	MovingVisitor movingVisitor;
	selection->Accept(diagram, movingVisitor, distanceX, distanceY);
	this->ChangeDefault(mouseLButton);
}
void MultipleSelectionState::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	Long i = 0;
	Long index = -1;

	while (i < selection->GetLength() && index == -1 ) {
		index = selection->SelectByPoint(startX, startY);
		i++;
	}
	if (index == -1) {
		selection->DeleteAllItems();
		this->ChangeDefault(mouseLButton);
	
	}
}

void MultipleSelectionState::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPaintDC) {

}