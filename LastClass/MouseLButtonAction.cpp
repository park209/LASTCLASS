//MouseLButtonAction.cpp

#include "MouseLButtonAction.h"

void MouseLButtonAction::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){

}

void MouseLButtonAction::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){
}

void MouseLButtonAction::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *cPatinDC) {
}

void MouseLButtonAction::ChangeState(MouseLButton* mouseLButton, MouseLButtonAction *mouseLButtonAction, UINT nChar) {
	mouseLButton->ChangeState(mouseLButtonAction, nChar);
}
void MouseLButtonAction::ChangeDefault(MouseLButton* mouseLButton) {
	mouseLButton->ChangeDefault();
}