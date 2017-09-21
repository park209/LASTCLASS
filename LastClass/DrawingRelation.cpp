#include "DrawingRelation.h"
#include "DefaultState.h"
DrawingRelation* DrawingRelation::instance = 0;

MouseLButtonAction* DrawingRelation::Instance() {
	if (instance == 0) {
		instance = new DrawingRelation;
	}
	return instance;
}

void DrawingRelation::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){
	this->ChangeState(mouseLButton, DefaultState::Instance());

}
void DrawingRelation::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){

}

void DrawingRelation::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPaintDC) {
	
		CPen pen;
		pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		CPen *oldPen = cPaintDC->SelectObject(&pen);
		cPaintDC->SetBkMode(TRANSPARENT);
		cPaintDC->MoveTo(startX, startY);
		cPaintDC->LineTo(currentX, currentY);
		cPaintDC->SelectObject(oldPen);
		pen.DeleteObject();
	
}