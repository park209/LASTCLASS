#include "MouseLButton.h"
#include "MouseLButtonAction.h"
#include "DrawingClass.h"


MouseLButton::MouseLButton() {
	this->state = DrawingClass::Instance();
	this->buttonState = 0;
}
void MouseLButton::MouseLButtonUp(Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	this->state->MouseLButtonUp(diagram, selection, startX, startY, currentX, currentY);
}
void MouseLButton::MouseLButtonDown(Long startX, Long startY, Long currentX, Long currentY, CPaintDC *cPatinDC) {
	this->state->MouseLButtonDown(startX, startY, currentX, currentY, cPatinDC);
}
void MouseLButton::ChangeState(UINT nChar) {
	this->buttonState = nChar;
}
void MouseLButton::ChangeState(MouseLButtonAction *mouseLButtonAction) {
	this->state = mouseLButtonAction;
}