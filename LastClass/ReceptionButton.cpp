//ReceptionButton.h


#include"ReceptionButton.h"
#include"DrawingController.h"
#include"Diagram.h"
#include"Class.h"
#include"DrawingController.h"
#include"Selection.h"
#include"Template.h"

ReceptionButton::ReceptionButton() {

}

ReceptionButton::ReceptionButton(const ReceptionButton& source) {

}

ReceptionButton::~ReceptionButton() {

}

void ReceptionButton::ChangeState(DrawingController *drawingController, UINT nChar) {
	ButtonState::ChangeState(drawingController, nChar);
}

Figure* ReceptionButton::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
	Class *object = 0;
	Figure *figure = 0;
	Long index;

	if (selection->GetLength() == 1 && dynamic_cast<Class*>(selection->GetAt(0))) {
		object = static_cast<Class*>(selection->GetAt(0));
		index = object->AddReception(diagram);
		figure = object->GetAt(index);
	}
	return figure;
}

void ReceptionButton::Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {

}

ReceptionButton& ReceptionButton::operator=(const ReceptionButton& source) {
	return const_cast<ReceptionButton&>(source);
}