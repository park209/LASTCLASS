#include "MovingObject.h"
#include "Figure.h"
#include "Selection.h"
#include "Finder.h"
#include "Line.h"
#include "SelectionState.h"
#include "Relation.h"
#include "Diagram.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "RollNameBox.h"

MovingObject* MovingObject::instance = 0;

MouseLButtonAction* MovingObject::Instance() {
	if (instance == 0) {
		instance = new MovingObject;
	}
	return instance;
}

void MovingObject::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	classDiagramForm->historyGraphic->PushUndo(diagram);

	if (dynamic_cast<FigureComposite*>(selection->GetAt(0))) {
		MovingVisitor movingVisitor;
		FigureComposite *figures = static_cast<FigureComposite*>(selection->GetAt(0));
		Finder finder;
		Long i = 0;
		Long j = 0;
		bool ret = false;

		CRect cRect1(figures->GetX() + (currentX - startX), figures->GetY() + (currentY - startY), figures->GetX() + (currentX - startX) + figures->GetWidth(), figures->GetY() + (currentY - startY) + figures->GetHeight());
		ret = diagram->CheckOverlapSelection(cRect1, selection);

		//CRect cRect1(figures->GetX() + (currentX - startX), figures->GetY() + (currentY - startY), figures->GetX() + (currentX - startX) + figures->GetWidth(), figures->GetY() + (currentY - startY) + figures->GetHeight());
		//while (i < diagram->GetLength() && ret != true) {
		//	FigureComposite *figureComposite = static_cast<FigureComposite*>(diagram->GetAt(i));
		//	CRect cRect2(figureComposite->GetX(), figureComposite->GetY(), figureComposite->GetX() + figureComposite->GetWidth(), figureComposite->GetY() + figureComposite->GetHeight());
		//	ret = finder.FindRectangleByArea(cRect2, cRect1);
		//	if (figures == figureComposite) {
		//		ret = false;
		//	}
		//	i++;
		//}

		// FigureComposite에 관계선 점 겹치면 점 Remove
		i = 0;
		while (i < figures->GetLength()) {
			if (dynamic_cast<Relation*>(figures->GetAt(i))) {
				Relation *object = static_cast<Relation*>(figures->GetAt(i));
				j = 0;
				while (j < object->GetLength()) {
					CPoint cPoint = object->GetAt(j);
					bool ret1 = finder.FindRectangleByPoint(cRect1, cPoint.x, cPoint.y);
					if (ret1 == true) {
						object->Remove(j);
						CPoint startPoint{ object->GetX(), object->GetY() };
						CPoint endPoint{ object->GetAt(0).x, object->GetAt(0).y };
						cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
						cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
						object->rollNamePoints->Modify(0, cPoint1);
						object->rollNamePoints->Modify(3, cPoint4);
						CPoint startPoint3{ object->GetAt(object->GetLength() - 1).x,
							object->GetAt(object->GetLength() - 1).y };
						CPoint endPoint3{ object->GetX() + object->GetWidth() , object->GetY() + object->GetHeight() };
						cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
						cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
						object->rollNamePoints->Modify(2, cPoint3);
						object->rollNamePoints->Modify(4, cPoint5);

						if (object->GetLength() % 2 > 0) {
							CPoint startPoint2{ object->GetAt((object->GetLength() - 1) / 2).x,
								object->GetAt((object->GetLength() - 1) / 2).y };
							cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
							object->rollNamePoints->Modify(1, cPoint2);

						}
						else {
							CPoint startPoint2{ object->GetAt((object->GetLength() - 1) / 2).x,
								object->GetAt((object->GetLength() - 1) / 2).y };
							CPoint endPoint2{ object->GetAt((object->GetLength() - 1) / 2 + 1).x,
								object->GetAt((object->GetLength() - 1) / 2 + 1).y };
							cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
							object->rollNamePoints->Modify(1, cPoint2);
						}

						j--;
					}
					j++;
				}
			}
			i++;
		}
		if (ret == false) {
			Long distanceX = currentX - startX;
			Long distanceY = currentY - startY;
			selection->Accept(diagram, movingVisitor, distanceX, distanceY);
		}
		//this->ChangeState(mouseLButton, SelectionState::Instance());
	}
	this->ChangeState(mouseLButton, SelectionState::Instance());
}

void MovingObject::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	selection->DeleteAllItems();
	selection->SelectByPoint(diagram, currentX, currentY);
	if (selection->GetLength() == 0) {
		this->ChangeDefault(mouseLButton);
	}
}

void MovingObject::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {

	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);

	Long distanceX = currentX - startX;
	Long distanceY = currentY - startY;
	Long i = 0;
	Long j = 0;
	Figure *figure;

	figure = selection->GetAt(i);
	if (dynamic_cast<FigureComposite*>(figure)) { //클래스나 메모면
												  // 해당 클래스나 메모 이동
		pDC->Rectangle(figure->GetX() + distanceX, figure->GetY() + distanceY, figure->GetX() + figure->GetWidth() + distanceX,
			figure->GetY() + figure->GetHeight() + distanceY);
		FigureComposite *figureComposite = static_cast<FigureComposite*>(figure); // 형변환

		while (j < figureComposite->GetLength()) { // 형변환 한게 관리하면 배열 렝스까지
			figure = figureComposite->GetAt(j);
			if (dynamic_cast<Line*>(figure)) {
				pDC->MoveTo(figure->GetX() + distanceX, figure->GetY() + distanceY);
				pDC->LineTo(figure->GetX() + figure->GetWidth() + distanceX,
					figure->GetY() + figure->GetHeight() + distanceY);
			}
			j++;
		}
	}

	pDC->SelectObject(oldPen);
	pen.DeleteObject();

}