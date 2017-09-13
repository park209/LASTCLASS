//Unclicked.cpp

#include"Unclicked.h"
#include"DrawingController.h"




Unclicked::Unclicked() {

}

Unclicked::Unclicked(const Unclicked& source) {

}

Unclicked::~Unclicked() {

}

void Unclicked::ChangeState(DrawingController *drawingController, Long key) {
	ButtonState::ChangeState(drawingController, key);
}

void Unclicked::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {

}

void Unclicked::Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDc->SelectObject(&pen);
	cPaintDc->SetBkMode(TRANSPARENT);
	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(currentX, startY);
	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(startX, currentY);
	cPaintDc->MoveTo(currentX, startY);
	cPaintDc->LineTo(currentX, currentY);
	cPaintDc->MoveTo(startX, currentY);
	cPaintDc->LineTo(currentX, currentY);
	
	//cPaintDc->Rectangle(startX, startY, currentX, currentY);
	cPaintDc->SelectObject(oldPen);
	pen.DeleteObject();
}

Unclicked& Unclicked::operator=(const Unclicked& source) {
	return const_cast<Unclicked&>(source);
}