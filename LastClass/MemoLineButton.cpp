//MemoLineButton.cpp

#include"MemoLineButton.h"
#include"DrawingController.h"


#include"Diagram.h"
#include"Selection.h"
#include "Class.h"
#include"MemoLine.h"
#include"MemoBox.h"
#include"Finder.h"

MemoLineButton::MemoLineButton() {

}

MemoLineButton::MemoLineButton(const MemoLineButton& source) {
	
}

MemoLineButton::~MemoLineButton() {

}

void MemoLineButton::ChangeState(DrawingController *drawingController, UINT nChar) {
	ButtonState::ChangeState(drawingController, nChar);
}

Figure* MemoLineButton::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
	Long index;
	Figure *figure = 0;
	if (selection->GetLength() == 1 && dynamic_cast<FigureComposite*>(selection->GetAt(0))) {
		//Long endClass = this->diagram->Find(this->currentX, this->currentY);//자기자신 연결시 0 0 0 0 값 저장됨.. 수정요 2017_09_09
		//Long x = this->currentX;
		//Long y = this->currentY;

		selection->SelectByPoint(diagram, currentX, currentY);
		if(selection->GetLength() == 2 && selection->GetAt(0) != selection->GetAt(1) && (dynamic_cast<MemoBox*>(selection->GetAt(0)) || dynamic_cast<MemoBox*>(selection->GetAt(1)))) {
		//if (selection->GetLength() == 2 && selection->GetAt(0) != selection->GetAt(1)) {

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

			MemoLine object(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
			index = static_cast<FigureComposite*>(selection->GetAt(0))->Add(object.Clone());
			figure = static_cast<FigureComposite*>(selection->GetAt(0))->GetAt(index);
		}
	}
	return figure;
}
void MemoLineButton::Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {

	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDc->SelectObject(&pen);
	cPaintDc->SetBkMode(TRANSPARENT);
	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(currentX, currentY);
	cPaintDc->SelectObject(oldPen);
	pen.DeleteObject();
}

MemoLineButton& MemoLineButton::operator=(const MemoLineButton& source) {
	return const_cast<MemoLineButton&>(source);
}