//MemoBoxButton.cpp

#include"MemoBoxButton.h"
#include"Diagram.h"
#include"Class.h"
#include"DrawingController.h"


MemoBoxButton::MemoBoxButton() {

}

MemoBoxButton::MemoBoxButton(const MemoBoxButton& source) {

}

MemoBoxButton::~MemoBoxButton() {

}

void MemoBoxButton::ChangeState(DrawingController *drawingController, UINT nChar) {
	ButtonState::ChangeState(drawingController, nChar);
}

Figure* MemoBoxButton::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
	Long index;
	if (currentX - startX < 100) {
		currentX = startX + 100;
	}
	if (currentY - startY < 80) {
		currentY = startY + 80;
	}
	index = diagram->AddMemoBox(startX, startY, currentX - startX, currentY - startY);
	return diagram->GetAt(index);
}
void MemoBoxButton::Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDc->SelectObject(&pen);
	cPaintDc->SetBkMode(TRANSPARENT);
	cPaintDc->Rectangle(startX, startY, currentX, currentY);
	cPaintDc->SelectObject(oldPen);
	pen.DeleteObject();
}

MemoBoxButton& MemoBoxButton::operator=(const MemoBoxButton& source) {
	return const_cast<MemoBoxButton&>(source);
}