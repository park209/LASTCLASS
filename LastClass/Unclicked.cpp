//Unclicked.cpp

#include"Unclicked.h"
#include"DrawingController.h"
#include "Selection.h"
#include "Line.h"
#include"Relation.h"


Unclicked::Unclicked() {

}

Unclicked::Unclicked(const Unclicked& source) {

}

Unclicked::~Unclicked() {

}

void Unclicked::ChangeState(DrawingController *drawingController, UINT nChar) {
	ButtonState::ChangeState(drawingController, nChar);
}

Figure* Unclicked::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {

	CPoint cPoint;
	cPoint.x = currentX;
	cPoint.y = currentY;
	if (selection->GetLength() != 0) {
	if (dynamic_cast<Relation*>(selection->GetAt(0))) {

		static_cast<Relation*>(selection->GetAt(0))->Add(cPoint);
	}
}
	return  static_cast<Relation*>(selection->GetAt(0));
}

void Unclicked::Draw(Selection *selection,Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDc->SelectObject(&pen);
	cPaintDc->SetBkMode(TRANSPARENT);
	
	if (selection->GetLength() == 0) {
		cPaintDc->MoveTo(startX, startY);
		cPaintDc->LineTo(currentX, startY);
		cPaintDc->MoveTo(startX, startY);
		cPaintDc->LineTo(startX, currentY);
		cPaintDc->MoveTo(currentX, startY);
		cPaintDc->LineTo(currentX, currentY);
		cPaintDc->MoveTo(startX, currentY);
		cPaintDc->LineTo(currentX, currentY);
	}
	
	
	Long distanceX = currentX - startX;
	Long distanceY = currentY - startY;
	Long length = selection->GetLength();
	Long i = 0;
	Long j;
	Figure *figure;

	while (i < length) {
		figure = selection->GetAt(i);
		//figure->Move(distanceX, distanceY);
		if (dynamic_cast<FigureComposite*>(figure)) { //클래스나 메모면
			//figure->Move(distanceX, distanceY); // 해당 클래스나 메모 이동
			cPaintDc->Rectangle(figure->GetX() + distanceX, figure->GetY() + distanceY, figure->GetX() + figure->GetWidth() + distanceX,
				figure->GetY() + figure->GetHeight()+ distanceY);
			FigureComposite *figureComposite = static_cast<FigureComposite*>(figure); // 형변환
			j = 0;
			while (j < figureComposite->GetLength()) { // 형변환 한게 관리하면 배열 렝스까지
				figure = figureComposite->GetAt(j);
				if (dynamic_cast<Line*>(figure)) {
					cPaintDc->MoveTo(figure->GetX() + distanceX, figure->GetY() + distanceY);
					cPaintDc->LineTo(figure->GetX() + figure->GetWidth() + distanceX,
						figure->GetY() + figure->GetHeight() + distanceY);
				}
				//figure->Move(distanceX, distanceY);
				j++;
			}
		}
		//20170915
	   /*else if () {

		}*/
		i++;
	}

	cPaintDc->SelectObject(oldPen);
	pen.DeleteObject();
	
}

Unclicked& Unclicked::operator=(const Unclicked& source) {
	return const_cast<Unclicked&>(source);
}