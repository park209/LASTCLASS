#include "ClassButton.h"
#include "Diagram.h"
#include "Class.h"
#include "DefaultState.h"
#include "DrawingClass.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "Figure.h"
#include "Finder.h"
#include "Selection.h"
#include "SelectionState.h"
#include "DrawingRelation.h"

DefaultState* DefaultState::instance = 0;

MouseLButtonAction* DefaultState::Instance() {
	if (instance == 0) {
		instance = new DefaultState;
	}
	return instance;
}
void DefaultState::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){
	Finder finder; 
	CRect area(startX, startY, currentX, currentY);

	selection->SelectByArea(diagram, area);
	
	if (selection->GetLength() > 0) {
		this->ChangeState(mouseLButton, SelectionState::Instance());
	}
	else {
		this->ChangeState(mouseLButton, DefaultState::Instance());
	}

}
void DefaultState::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){
	UINT object = mouseLButton->GetButtonState();
	if (object == 49) {
		this->ChangeState(mouseLButton, DrawingClass::Instance());
	}
	selection->SelectByPoint(diagram, startX, startY);
	if (selection->GetLength() > 0) {
		this->ChangeState(mouseLButton, SelectionState::Instance());
	}
}
void DefaultState::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPaintDC) {
	//Long length = selection->GetLength();
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDC->SelectObject(&pen);
	cPaintDC->SetBkMode(TRANSPARENT);
	
	cPaintDC->MoveTo(startX, startY);
	cPaintDC->LineTo(currentX, startY);
	cPaintDC->MoveTo(startX, startY);
	cPaintDC->LineTo(startX, currentY);
	cPaintDC->MoveTo(currentX, startY);
	cPaintDC->LineTo(currentX, currentY);
	cPaintDC->MoveTo(startX, currentY);
	cPaintDC->LineTo(currentX, currentY);
}