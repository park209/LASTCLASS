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

void TemplateButton::ChangeState(DrawingController *drawingController, UINT nChar) {
	ButtonState::ChangeState(drawingController, nChar);
}

void TemplateButton::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
	Class *object;
	
	// �̰� ���ø� �ߺ����� ��� ��

	if (selection->GetLength() == 1 && dynamic_cast<Class*>(selection->GetAt(0))) {
			object = dynamic_cast<Class*>(selection->GetAt(0));
			object->AddTemplate(object->GetX() + object->GetWidth() - 70, object->GetY() - 15, 80, 25);
		}
	
}

void TemplateButton::Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {

}

TemplateButton& TemplateButton::operator=(const TemplateButton& source) {
	return const_cast<TemplateButton&>(source);
}