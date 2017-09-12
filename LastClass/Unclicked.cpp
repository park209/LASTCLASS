//Unclicked.cpp

#include"Unclicked.h"
#include"DrawingController.h"
#include"ClassButton.h"
#include"GeneralizationButton.h"

Unclicked::Unclicked() {

}

Unclicked::Unclicked(const Unclicked& source) {

}

Unclicked::~Unclicked() {

}

void Unclicked::ChangeState(DrawingController *drawingController, Long key) {
	if (key == 0) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new Unclicked;
	}
	if (key == 1) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new ClassButton;
	}
	if (key == 2) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new GeneralizationButton;
	}
}

void Unclicked::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {

}

Unclicked& Unclicked::operator=(const Unclicked& source) {
	return const_cast<Unclicked&>(source);
}