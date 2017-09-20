//AssociationButton.cpp

#include"AssociationButton.h"
#include"DrawingController.h"


#include"Diagram.h"
#include"Selection.h"
#include "SelfAssociation.h"
#include"Association.h"
#include"Class.h"
#include"Finder.h"

AssociationButton::AssociationButton() {

}

AssociationButton::AssociationButton(const AssociationButton& source) {

}

AssociationButton::~AssociationButton() {

}

void AssociationButton::ChangeState(DrawingController *drawingController, UINT nChar) {
	ButtonState::ChangeState(drawingController, nChar);
}

Figure* AssociationButton::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
	Long index;
	Figure *figure = 0;
	if (selection->GetLength() == 1 && dynamic_cast<Class*>(selection->GetAt(0))) {

		selection->SelectByPoint(diagram, currentX, currentY);

		if (selection->GetLength() == 2 && selection->GetAt(0) != selection->GetAt(1) && dynamic_cast<Class*>(selection->GetAt(1))) {

			CPoint lineStart(startX, startY);
			CPoint lineEnd(currentX, currentY);

			CRect rect(selection->GetAt(0)->GetX(), selection->GetAt(0)->GetY(),
				selection->GetAt(0)->GetX() + selection->GetAt(0)->GetWidth(),
				selection->GetAt(0)->GetY() + selection->GetAt(0)->GetHeight());

			Finder finder;
			CPoint cross1 = finder.GetCrossPoint(lineStart, lineEnd, rect);

			rect.left = selection->GetAt(1)->GetX();
			rect.top = selection->GetAt(1)->GetY();
			rect.right = selection->GetAt(1)->GetX() + selection->GetAt(1)->GetWidth();
			rect.bottom = selection->GetAt(1)->GetY() + selection->GetAt(1)->GetHeight();
			CPoint cross2 = finder.GetCrossPoint(lineStart, lineEnd, rect);

			Association object(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
			index = static_cast<FigureComposite*>(selection->GetAt(0))->Add(object.Clone());
			figure = static_cast<FigureComposite*>(selection->GetAt(0))->GetAt(index);
		}
		if (selection->GetLength() == 2 && selection->GetAt(0) == selection->GetAt(1)) {
			Class *object = static_cast<Class*>(selection->GetAt(0));
			SelfAssociation selfAssociation(object->GetX() + object->GetWidth() - 30, object->GetY(), 30, 30);
			index = object->Add(selfAssociation.Clone());
			figure = object->GetAt(index);
		}
	}
	return figure;
}
void AssociationButton::Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {
	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(currentX, currentY);
}
AssociationButton& AssociationButton::operator=(const AssociationButton& source) {
	return const_cast<AssociationButton&>(source);
}