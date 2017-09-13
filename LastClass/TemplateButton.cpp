//TemplateButton.h


#include"TemplateButton.h"
#include"DrawingController.h"
#include"Diagram.h"
#include"Class.h"
#include"DrawingController.h"
#include"Selection.h"
#include"Template.h"

TemplateButton::TemplateButton() {

}

TemplateButton::TemplateButton(const TemplateButton& source) {

}

TemplateButton::~TemplateButton() {

}

void TemplateButton::ChangeState(DrawingController *drawingController, Long key) {
	ButtonState::ChangeState(drawingController, key);
}

void TemplateButton::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
	Class *object;
	
	


		if (selection->GetLength() == 1) {
			object = dynamic_cast<Class*>(selection->GetAt(0));
			object->AddTemplate(object->GetX() + object->GetWidth() - 70, object->GetY() - 15, 80, 25);
		}
	
}

void TemplateButton::Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {

}

TemplateButton& TemplateButton::operator=(const TemplateButton& source) {
	return const_cast<TemplateButton&>(source);
}