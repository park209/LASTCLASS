//DrawingController.cpp

#include"DrawingController.h"
#include"ButtonState.h"
#include"Unclicked.h"

DrawingController::DrawingController() {
	this->buttonState = new Unclicked;
}

DrawingController::DrawingController(const DrawingController& source) {

}

DrawingController::~DrawingController() {
	if (this->buttonState != 0) {
		delete this->buttonState;
	}
}

void DrawingController::ChangeState(UINT nChar){
	this->buttonState->ChangeState(this, nChar);
}

Figure* DrawingController::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
	return  this->buttonState->AddToArray(diagram, selection, startX, startY, currentX, currentY);
}


void DrawingController::Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {
	this->buttonState->Draw(selection, startX, startY, currentX, currentY, cPaintDc);
}

DrawingController& DrawingController::operator=(const DrawingController& source) {

	return const_cast<DrawingController&>(source);
}
