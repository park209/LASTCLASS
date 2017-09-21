#include "ClassButton.h"
#include "Diagram.h"
#include "Class.h"
#include "DrawingMemoBox.h"
#include "Figure.h"
#include "DefaultState.h"

DrawingMemoBox* DrawingMemoBox::instance = 0;

MouseLButtonAction* DrawingMemoBox::Instance() {
	if (instance == 0) {
		instance = new DrawingMemoBox;
	}
	return instance;
}
void DrawingMemoBox::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	Long index;
	if (currentX - startX < 100) {
		currentX = startX + 100;
	}
	if (currentY - startY < 80) {
		currentY = startY + 80;
	}
	index = diagram->AddMemoBox(startX, startY, currentX - startX, currentY - startY);
	this->ChangeState(mouseLButton, DefaultState::Instance());
}
void DrawingMemoBox::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

}
void DrawingMemoBox::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPaintDC) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDC->SelectObject(&pen);
	cPaintDC->SetBkMode(TRANSPARENT);
	cPaintDC->Rectangle(startX, startY, currentX, currentY);
	cPaintDC->SelectObject(oldPen);
	pen.DeleteObject();
}