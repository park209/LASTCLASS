//ButtonState.cpp

#include"ButtonState.h"

ButtonState::ButtonState() {

}

ButtonState::ButtonState(const ButtonState& source) {

}

ButtonState::~ButtonState() {

}

void ButtonState::ChangeState(DrawingController *drawingController, Long key) {

}

void ButtonState::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {

}

ButtonState& ButtonState::operator=(const ButtonState& source) {
	return const_cast<ButtonState&>(source);
}