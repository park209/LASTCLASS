#include "ClassButton.h"
#include "Diagram.h"
#include "Class.h"
#include "SelectionState.h"
#include "DrawingClass.h"
#include "DrawingRelation.h"
#include "DefaultState.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "Figure.h"
#include "Finder.h"
#include "Line.h"
#include "Selection.h"

SelectionState* SelectionState::instance = 0;

MouseLButtonAction* SelectionState::Instance() {
	if (instance == 0) {
		instance = new SelectionState;
	}
	return instance;
}
void SelectionState::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){
	//selection->DeleteAllItems();
	//selection->SelectByPoint(diagram, currentX, currentY);
	selection->GetAt(0);
	selection->GetAt(1);
	if (selection->GetLength() == 0) {
		this->ChangeState(mouseLButton, DefaultState::Instance());
	}
	if(selection->GetLength() ==1) {
		selection->GetLength();
		MovingVisitor movingVisitor;
		Long distanceX = currentX - startX;
		Long distanceY = currentY - startY;
		selection->Accept(diagram, movingVisitor, distanceX, distanceY);
	}
}
void SelectionState::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){
	selection->DeleteAllItems();
	selection->SelectByPoint(diagram, currentX, currentY);
	if (selection->GetLength() == 0) {
		this->ChangeState(mouseLButton, DefaultState::Instance());
	}
}
void SelectionState::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPaintDC) {
	//CPen pen;
	//pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	//CPen *oldPen = cPaintDC->SelectObject(&pen);
	//cPaintDC->SetBkMode(TRANSPARENT);


	//Long distanceX = currentX - startX;
	//Long distanceY = currentY - startY;
	//Long i = 0;
	//Long j = 0;
	//Figure *figure;

	//figure = selection->GetAt(i);
	//if (dynamic_cast<FigureComposite*>(figure)) { //클래스나 메모면
	//											  // 해당 클래스나 메모 이동
	//	cPaintDC->Rectangle(figure->GetX() + distanceX, figure->GetY() + distanceY, figure->GetX() + figure->GetWidth() + distanceX,
	//		figure->GetY() + figure->GetHeight() + distanceY);
	//	FigureComposite *figureComposite = static_cast<FigureComposite*>(figure); // 형변환

	//	while (j < figureComposite->GetLength()) { // 형변환 한게 관리하면 배열 렝스까지
	//		figure = figureComposite->GetAt(j);
	//		if (dynamic_cast<Line*>(figure)) {
	//			cPaintDC->MoveTo(figure->GetX() + distanceX, figure->GetY() + distanceY);
	//			cPaintDC->LineTo(figure->GetX() + figure->GetWidth() + distanceX,
	//				figure->GetY() + figure->GetHeight() + distanceY);
	//		}
	//		j++;
	//	}
	//}
	//cPaintDC->SelectObject(oldPen);
	//pen.DeleteObject();
	if (mouseLButton->GetButtonState() == 50) {
		this->ChangeState(mouseLButton, DrawingRelation::Instance(),50);
	}
}