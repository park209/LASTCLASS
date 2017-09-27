#include "MovingRelation.h"
#include "Relation.h"
#include "Finder.h"
#include "Selection.h"
#include "Diagram.h"

MovingRelation* MovingRelation::instance = 0;

MouseLButtonAction* MovingRelation::Instance() {
	if (instance == 0) {
		instance = new MovingRelation;
	}
	return instance;
}

void MovingRelation::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
		Relation *relation = static_cast<Relation*>(selection->GetAt(0));
		bool point = false;
		bool startLine = false;
		bool squareFace = false;
		bool endLine = false;
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

		CRect object(relation->GetX() - 10, relation->GetY() - 10, relation->GetX() + 10, relation->GetY() + 10);
		startLine = finder.FindRectangleByPoint(object, startX, startY);
		if (startLine == true) {

			Figure *figure = finder.GetParents(diagram, relation);
			Long x = figure->GetX();
			Long y = figure->GetY();
			Long width = figure->GetWidth();
			Long height = figure->GetHeight();
			Long relationX = currentX;
			Long relationY = currentY;
			if (x + width < currentX) {
				relationX = x + width - 1;
			}
			else if (x > currentX) {
				relationX = x + 1;
			}
			if (y + height < currentY) {
				relationY = y + height - 1;
			}
			else if (y > currentY) {
				relationY = y + 1;
			}

			CRect rect(x, y, x + width, y + height);
			Finder finder;
			CPoint startLine(relationX, relationY);
			CPoint endLine(relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight());
			CPoint cross = finder.GetCrossPoint(startLine, endLine, rect);
			relation->Modify(cross.x, cross.y, relation->GetWidth() + relation->GetX() - cross.x, relation->GetHeight() + relation->GetY() - cross.y);
			
		}
		else { // 끝점찾기
			Long i = 0;
			FigureComposite *figures = 0;
			while (i < diagram->GetLength() && endLine != true) {
				figures = static_cast<FigureComposite*>(diagram->GetAt(i));
				CRect object(figures->GetX(), figures->GetY(), figures->GetX() + figures->GetWidth(), figures->GetY() + figures->GetHeight());
				endLine = finder.FindRectangleByPoint(object, relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight());
				i++;
			}
			if (endLine == true) {
				//끝점 변경하는 로직.
				Long x = figures->GetX();
				Long y = figures->GetY();
				Long width = figures->GetWidth();
				Long height = figures->GetHeight();
				Long relationX = currentX;
				Long relationY = currentY;
				if (x + width < currentX) {
					relationX = x + width - 1;
				}
				else if (x > currentX) {
					relationX = x + 1;
				}
				if (y + height < currentY) {
					relationY = y + height - 1;
				}
				else if (y > currentY) {
					relationY = y + 1;
				}

				CRect rect(x, y, x + width, y + height);
				Finder finder;
				CPoint startLine(relation->GetX(), relation->GetY());
				CPoint endLine(relationX , relationY);
				CPoint cross = finder.GetCrossPoint(startLine, endLine, rect);
				relation->Modify(relation->GetX() , relation->GetY() , cross.x - relation->GetX()  , cross.y -relation->GetY());
			}
		}
	this->ChangeDefault(mouseLButton);
}
void MovingRelation::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

}
void MovingRelation::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPaintDC) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDC->SelectObject(&pen);
	cPaintDC->SetBkMode(TRANSPARENT);

	Relation *relation = static_cast<Relation*>(selection->GetAt(0));
	bool startLine = false;
	bool endLine = false;
	CPoint lineStart;
	CPoint lineEnd;
	Finder finder;

	//시작점 찾기
	CRect object(relation->GetX() - 10, relation->GetY() - 10, relation->GetX() + 10, relation->GetY() + 10);
	startLine = finder.FindRectangleByPoint(object, startX, startY);
	if (startLine == true) {
		Figure *figure = finder.GetParents(diagram, relation);
		Long x = figure->GetX();
		Long y = figure->GetY();
		Long width = figure->GetWidth();
		Long height = figure->GetHeight();
		Long relationX = currentX;
		Long relationY = currentY;
		if (x + width < currentX) {
			relationX = x + width - 1;
		}
		else if (x > currentX) {
			relationX = x -1;
		}
		else if (x > currentX) {
			relationX = x + 1;
		}
		if (y + height < currentY) {
			relationY = y + height - 1;
		}
		else if (y > currentY) {
			relationY =y - 1;
		}
		else if (y > currentY) {
			relationY = y + 1;
		}
		lineStart.x = relationX;
		lineStart.y = relationY;
		if (relation->GetLength() > 0) {
			lineEnd.x = relation->GetAt(0).x;
			lineEnd.y = relation->GetAt(0).y;
		}
		else{
			lineEnd.x = relation->GetX() + relation->GetWidth();
			lineEnd.y = relation->GetY() + relation->GetHeight();
		}

	}
	else { // 끝점찾기
		Long i = 0;
		FigureComposite *figures = 0;
		while (i < diagram->GetLength() && endLine != true) {
			figures = static_cast<FigureComposite*>(diagram->GetAt(i));
			CRect object(figures->GetX(), figures->GetY(), figures->GetX() + figures->GetWidth(), figures->GetY() + figures->GetHeight());
			endLine = finder.FindRectangleByPoint(object, relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight());
			i++;
		}
		if (endLine == true) {
			//끝점 
			Long x = figures->GetX();
			Long y = figures->GetY();
			Long width = figures->GetWidth();
			Long height = figures->GetHeight();
			Long relationX = currentX;
			Long relationY = currentY;
			if (x + width < currentX) {
				relationX = x + width - 1;
			}
			else if (x > currentX) {
				relationX = x + 1;
			}
			if (y + height < currentY) {
				relationY = y + height - 1;
			}
			else if (y > currentY) {
				relationY = y + 1;
			}


			CRect rect(x, y, x + width, y + height);
			Finder finder;
			CPoint startLine(relation->GetX(), relation->GetY());
			CPoint endLine(relationX, relationY);
			CPoint cross = finder.GetCrossPoint(startLine, endLine, rect);

			if (relation->GetLength() > 0) {
				lineStart.x = relation->GetAt(relation->GetLength() -1).x;
				lineStart.y = relation->GetAt(relation->GetLength() - 1).y;
			}
			else {

				lineStart.x = relation->GetX();
				lineStart.y = relation->GetY();
			}
			lineEnd.x = cross.x ;
			lineEnd.y = cross.y ;
		}
	}
	cPaintDC->MoveTo(lineStart.x, lineStart.y);
	cPaintDC->LineTo(lineEnd.x, lineEnd.y);
	cPaintDC->SelectObject(oldPen);
	pen.DeleteObject();

}
