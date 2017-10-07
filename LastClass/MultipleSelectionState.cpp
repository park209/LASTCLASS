#include "MultipleSelectionState.h"
#include "Selection.h"
#include "Relation.h"
#include "MovingVisitor.h"
#include "Diagram.h"
#include "SelfRelation.h"
#include "RollNameBox.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"

MultipleSelectionState* MultipleSelectionState::instance = 0;

MouseLButtonAction* MultipleSelectionState::Instance() {
	if (instance == 0) {
		instance = new MultipleSelectionState;
	}
	return instance;
}

void MultipleSelectionState::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	Long length = selection->GetLength();
	Long i = 0;
	Long j;
	Long k = 0;
	Long l = 0;
	Figure *figure;
	Long distanceX = currentX - startX;
	Long distanceY = currentY - startY;
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;

	classDiagramForm->historyGraphic->PushUndo(diagram);
	while (i < length) {
		figure = selection->GetAt(i);

		if (dynamic_cast<FigureComposite*>(figure)) { //클래스나 메모면
			Long startX = figure->GetX();
			Long startY = figure->GetY();
			Long endX = figure->GetX() + figure->GetWidth();
			Long endY = figure->GetY() + figure->GetHeight();
			figure->Move(distanceX, distanceY); // 해당 클래스나 메모 이동
			FigureComposite *figureComposite = static_cast<FigureComposite*>(figure); // 형변환
			j = 0;
			while (j < figureComposite->GetLength()) { // 형변환 한게 관리하면 배열 렝스까지
				figure = figureComposite->GetAt(j);
				figure->Move(distanceX, distanceY);
				if (dynamic_cast<Relation*>(figureComposite->GetAt(j))) {
					Relation *relation = static_cast<Relation*>(figureComposite->GetAt(j));
					//
					CPoint startPoint{ relation->GetX(), relation->GetY() };
					CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
					cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
					cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
					cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
					cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
					cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
					relation->rollNamePoints->Modify(0, cPoint1);
					relation->rollNamePoints->Modify(1, cPoint2);
					relation->rollNamePoints->Modify(2, cPoint3);
					relation->rollNamePoints->Modify(3, cPoint4);
					relation->rollNamePoints->Modify(4, cPoint5);

					//
					Long m = 0;
					while (m < relation->GetLength()) {
						CPoint point(relation->GetAt(m).x + distanceX, relation->GetAt(m).y + distanceY);
						relation->Move(m, point);
						m++;
					}
				}
				if (dynamic_cast<SelfRelation*>(figureComposite->GetAt(j))) {
					//
					SelfRelation *selfRelation = static_cast<SelfRelation*>(figureComposite->GetAt(j));
					CPoint startPoint1And4{ selfRelation->GetX(), selfRelation->GetY() };
					CPoint endPoint1And4{ selfRelation->GetX() ,  selfRelation->GetY() - 40 };

					CPoint startPoint2{ selfRelation->GetX(), selfRelation->GetY() - 40 };
					CPoint endPoint2{ selfRelation->GetX() + 80,  selfRelation->GetY() - 40 };

					CPoint startPoint3And5{ selfRelation->GetX() + 80, selfRelation->GetY() + 40 };
					CPoint endPoint3And5{ selfRelation->GetX() + 30,  selfRelation->GetY() + 40 };
					cPoint1 = rollNameBoxesPoint->GetSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4);
					cPoint2 = rollNameBoxesPoint->GetSelfRelationSecondRollNamePoint(startPoint2, endPoint2);
					cPoint3 = rollNameBoxesPoint->GetSelfRelationThirdRollNamePoint(startPoint3And5, endPoint3And5);
					cPoint4 = rollNameBoxesPoint->GetSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4);
					cPoint5 = rollNameBoxesPoint->GetSelfRelationFifthRollNamePoint(startPoint3And5, endPoint3And5);
					selfRelation->rollNamePoints->Modify(0, cPoint1);
					selfRelation->rollNamePoints->Modify(1, cPoint2);
					selfRelation->rollNamePoints->Modify(2, cPoint3);
					selfRelation->rollNamePoints->Modify(3, cPoint4);
					selfRelation->rollNamePoints->Modify(4, cPoint5);
				}

				j++;
			}
			k = 0;
			while (k < diagram->GetLength()) {
				figureComposite = static_cast<FigureComposite*>(diagram->GetAt(k));
				l = 0;
				while (l < figureComposite->GetLength()) {
					if (dynamic_cast<Relation*>(figureComposite->GetAt(l))) {
						Relation *relation = static_cast<Relation*>(figureComposite->GetAt(l));
						Long relationEndX = relation->GetX() + relation->GetWidth();
						Long relationEndY = relation->GetY() + relation->GetHeight();
						if (startX <= relationEndX &&  relationEndX <= endX &&
							startY <= relationEndY &&  relationEndY <= endY) {
							relation->EndPointMove(distanceX, distanceY);
							//
							CPoint startPoint{ relation->GetX(), relation->GetY() };
							CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
							cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
							cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
							cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
							cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
							cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
							relation->rollNamePoints->Modify(0, cPoint1);
							relation->rollNamePoints->Modify(1, cPoint2);
							relation->rollNamePoints->Modify(2, cPoint3);
							relation->rollNamePoints->Modify(3, cPoint4);
							relation->rollNamePoints->Modify(4, cPoint5);
							Long h = 0;

						}

					}
					l++;
				}
				k++;
			}

		}
		i++;
	}
	this->ChangeDefault(mouseLButton);
}
void MultipleSelectionState::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	Long i = 0;
	Long index = -1;

	while (i < selection->GetLength() && index == -1) {
		index = selection->SelectByPoint(startX, startY);
		i++;
	}
	if (index == -1) {
		selection->DeleteAllItems();
		this->ChangeDefault(mouseLButton);

	}
}

void MultipleSelectionState::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {

}