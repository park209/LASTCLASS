#include "MultipleSelectionState.h"
#include "Selection.h"
#include "Relation.h"
#include "MovingVisitor.h"
#include "Diagram.h"

MultipleSelectionState* MultipleSelectionState::instance = 0;

MouseLButtonAction* MultipleSelectionState::Instance() {
	if (instance == 0) {
		instance = new MultipleSelectionState;
	}
	return instance;
}

void MultipleSelectionState::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	Long length = selection->GetLength();
	Long i = 0;
	Long j;
	Long k = 0;
	Long l = 0;
	Figure *figure;
	Long distanceX = currentX - startX;
	Long distanceY = currentY - startY;

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
					Long m = 0;
					while (m < relation->GetLength()) {
						CPoint point(relation->GetAt(m).x + distanceX, relation->GetAt(m).y + distanceY);
						relation->Move(m, point);
						m++;
					}
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

	while (i < selection->GetLength() && index == -1 ) {
		index = selection->SelectByPoint(startX, startY);
		i++;
	}
	if (index == -1) {
		selection->DeleteAllItems();
		this->ChangeDefault(mouseLButton);
	
	}
}

void MultipleSelectionState::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPaintDC) {

}