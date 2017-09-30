//MouseButton.cpp

#include "MouseLButton.h"
#include "MouseLButtonAction.h"
#include "DrawingClass.h"
#include "DefaultState.h"


MouseLButton::MouseLButton() {
	this->state = DefaultState::Instance();
	this->buttonState = 0;
}
void MouseLButton::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){
	this->state->MouseLButtonUp(this, diagram, selection, startX, startY, currentX, currentY);
}
void MouseLButton::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){
	this->state->MouseLButtonDown(this, diagram, selection, startX, startY, currentX, currentY);
}
void MouseLButton::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC){
	this->state->MouseLButtonDrag(this, diagram, selection, startX, startY, currentX, currentY, pDC);
}
void MouseLButton::ChangeState(UINT nChar) {
	this->buttonState = nChar;
}
void MouseLButton::ChangeDefault() {
	this->buttonState = 0;
	this->state = DefaultState::Instance();
}
void MouseLButton::ChangeState(MouseLButtonAction *mouseLButtonAction,UINT nChar) {
	this->state = mouseLButtonAction;
	this->buttonState = nChar;
}