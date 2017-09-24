//MultipleSelectionState.cpp

#include "MultipleSelectionState.h"


MultipleSelectionState* MultipleSelectionState::instance = 0;

MouseLButtonAction* MultipleSelectionState::Instance() {
	if (instance == 0) {
		instance = new MultipleSelectionState;
	}
	return instance;
}

void MultipleSelectionState::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

}
void MultipleSelectionState::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

}

void MultipleSelectionState::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPaintDC) {

}