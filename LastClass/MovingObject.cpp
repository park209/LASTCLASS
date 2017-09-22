#include "MovingObject.h"
#include "Figure.h"
#include "Selection.h"
#include "Finder.h"
#include "Line.h"
#include "SelectionState.h"
#include "Relation.h"

MovingObject* MovingObject::instance = 0;

MouseLButtonAction* MovingObject::Instance() {
	if (instance == 0) {
		instance = new MovingObject;
	}
	return instance;
}

void MovingObject::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	//selection->DeleteAllItems();
	//selection->SelectByPoint(diagram, currentX, currentY);

	if (dynamic_cast<FigureComposite*>(selection->GetAt(0))) {
		MovingVisitor movingVisitor;
		Long distanceX = currentX - startX;
		Long distanceY = currentY - startY;
		selection->Accept(diagram, movingVisitor, distanceX, distanceY);
		this->ChangeState(mouseLButton, SelectionState::Instance());
	}

	if (dynamic_cast<Relation*>(selection->GetAt(0))) {
		Relation *relation = static_cast<Relation*>(selection->GetAt(0));
		bool ret = false;
		CPoint lineStart(relation->GetX(), relation->GetY());
		CPoint lineEnd;
		Long index = 0;
		Finder finder;
		CPoint startCPoint;
		CPoint currentCPoint;
		startCPoint.x = startX;
		startCPoint.y = startY;
		currentCPoint.x = currentX;
		currentCPoint.y = currentY;

		while (index < relation->GetLength() && ret == false) {
			CRect rect(relation->GetAt(index).x - 5, relation->GetAt(index).y - 5, relation->GetAt(index).x + 5, relation->GetAt(index).y + 5);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			index++;
		}
		if (ret == true) {
			CPoint point(currentX, currentY);
			relation->Move(index - 1, point);
		}
		else {
			Long i = 0;
			while (i < relation->GetLength() && ret == false) {
				lineEnd.x = relation->GetAt(i).x;
				lineEnd.y = relation->GetAt(i).y;
				ret = finder.FindLineByPoint(lineStart, lineEnd, startX, startY);
				lineStart.x = lineEnd.x;
				lineStart.y = lineEnd.y;
				i++;
			}

			lineEnd.x = relation->GetWidth() + relation->GetX();
			lineEnd.y = relation->GetHeight() + relation->GetY();
			if (ret == false) {
				ret = finder.FindLineByPoint(lineStart, lineEnd, startX, startY);
			}
			if (ret == true) {
				relation->Add(startCPoint, currentCPoint);
			}
		}
	}
	this->ChangeState(mouseLButton, SelectionState::Instance());
}
void MovingObject::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

}

void MovingObject::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPaintDC) {

	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDC->SelectObject(&pen);
	cPaintDC->SetBkMode(TRANSPARENT);


	Long distanceX = currentX - startX;
	Long distanceY = currentY - startY;
	Long i = 0;
	Long j = 0;
	Figure *figure ;

	figure = selection->GetAt(i);
	if (dynamic_cast<FigureComposite*>(figure)) { //클래스나 메모면
												  // 해당 클래스나 메모 이동
		cPaintDC->Rectangle(figure->GetX() + distanceX, figure->GetY() + distanceY, figure->GetX() + figure->GetWidth() + distanceX,
			figure->GetY() + figure->GetHeight() + distanceY);
		FigureComposite *figureComposite = static_cast<FigureComposite*>(figure); // 형변환

		while (j < figureComposite->GetLength()) { // 형변환 한게 관리하면 배열 렝스까지
			figure = figureComposite->GetAt(j);
			if (dynamic_cast<Line*>(figure)) {
				cPaintDC->MoveTo(figure->GetX() + distanceX, figure->GetY() + distanceY);
				cPaintDC->LineTo(figure->GetX() + figure->GetWidth() + distanceX,
					figure->GetY() + figure->GetHeight() + distanceY);
			}
			j++;
		}
	}


	bool ret = false;
	if ( dynamic_cast<Relation*>(selection->GetAt(0))) {
		Relation *relation = static_cast<Relation*>(selection->GetAt(0));
		Finder finder;

		CPoint lineStart(relation->GetX(), relation->GetY());
		Long index = 0;
		CPoint lineEnd;

		while (index < relation->GetLength() && ret == false) {
			CRect rect(relation->GetAt(index).x - 5, relation->GetAt(index).y - 5, relation->GetAt(index).x + 5, relation->GetAt(index).y + 5);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			index++;
		}

		if (ret == true && relation->GetLength() == 1) {
			lineEnd.x = relation->GetX() + relation->GetWidth();
			lineEnd.y = relation->GetY() + relation->GetHeight();
		}

		else if (ret == true && index == 1 && index < relation->GetLength()) {
			lineEnd.x = relation->GetAt(index).x;
			lineEnd.y = relation->GetAt(index).y;
		}
		else if (ret == true && index == relation->GetLength()) {
			lineStart.x = relation->GetAt(index - 2).x;
			lineStart.y = relation->GetAt(index - 2).y;
			lineEnd.x = relation->GetX() + relation->GetWidth();
			lineEnd.y = relation->GetY() + relation->GetHeight();
		}

		else if (ret == true) {
			lineStart.x = relation->GetAt(index - 2).x;
			lineStart.y = relation->GetAt(index - 2).y;
			lineEnd.x = relation->GetAt(index).x;
			lineEnd.y = relation->GetAt(index).y;
		}

		index = 0;
		while (index < relation->GetLength() && ret == false) {
			lineEnd.x = relation->GetAt(index).x;
			lineEnd.y = relation->GetAt(index).y;
			ret = finder.FindLineByPoint(lineStart, lineEnd, startX, startY);
			if (ret == false) {
				lineStart.x = lineEnd.x;
				lineStart.y = lineEnd.y;
			}
			index++;
		}
		if (ret == false) {
			lineEnd.x = relation->GetWidth() + relation->GetX();
			lineEnd.y = relation->GetHeight() + relation->GetY();
			ret = finder.FindLineByPoint(lineStart, lineEnd, startX, startY);
		}
		if (ret == true) {
			cPaintDC->MoveTo(lineStart.x, lineStart.y);
			cPaintDC->LineTo(currentX, currentY);
			cPaintDC->MoveTo(lineEnd.x, lineEnd.y);
			cPaintDC->LineTo(currentX, currentY);
		}
	}


	cPaintDC->SelectObject(oldPen);
	pen.DeleteObject();

}