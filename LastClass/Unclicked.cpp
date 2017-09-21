//Unclicked.cpp
#include"Unclicked.h"
#include"DrawingController.h"
#include "Selection.h"
#include "Line.h"
#include"Relation.h"
#include "Finder.h"
#include"Class.h"
#include"Template.h"
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
	Finder finder;
	CPoint startCPoint;
	CPoint currentCPoint;
	startCPoint.x = startX;
	startCPoint.y = startY;
	currentCPoint.x = currentX;
	currentCPoint.y = currentY;

	if (selection->GetLength() == 1 && dynamic_cast<Relation*>(selection->GetAt(0))) {

		Relation *relation = static_cast<Relation*>(selection->GetAt(0));
		bool ret = false;
		CPoint lineStart(relation->GetX(), relation->GetY());
		CPoint lineEnd;
		Long index = 0;

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
	else if (selection->GetLength() == 1 && dynamic_cast<FigureComposite*>(selection->GetAt(0))) {
		FigureComposite *figureComposite = static_cast<FigureComposite*>(selection->GetAt(0));
		bool ret = false;


	}
	return  selection->GetAt(0);
}

void Unclicked::Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {
	Long length = selection->GetLength();
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDc->SelectObject(&pen);
	cPaintDc->SetBkMode(TRANSPARENT);
	if (length == 0) {
		cPaintDc->MoveTo(startX, startY);
		cPaintDc->LineTo(currentX, startY);
		cPaintDc->MoveTo(startX, startY);
		cPaintDc->LineTo(startX, currentY);
		cPaintDc->MoveTo(currentX, startY);
		cPaintDc->LineTo(currentX, currentY);
		cPaintDc->MoveTo(startX, currentY);
		cPaintDc->LineTo(currentX, currentY);
	}
	bool ret = false;
	if (length == 1 && dynamic_cast<Relation*>(selection->GetAt(0))) {
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
			cPaintDc->MoveTo(lineStart.x, lineStart.y);
			cPaintDc->LineTo(currentX, currentY);
			cPaintDc->MoveTo(lineEnd.x, lineEnd.y);
			cPaintDc->LineTo(currentX, currentY);
		}
	}

	if (length == 1 && dynamic_cast<FigureComposite*>(selection->GetAt(0))) {
		FigureComposite *object = static_cast<FigureComposite*>(selection->GetAt(0));
		CRect rect;
		Finder finder;

		if (dynamic_cast<Class*>(object) && static_cast<Class*>(object)->GetTempletePosition() != -1) {
			Class *selectedClass = static_cast<Class*>(object);
			Template *templete = static_cast<Template*>(selectedClass->GetAt(selectedClass->GetTempletePosition()));
			if (ret == false) { // 좌상단
				CRect rect(selectedClass->GetX() - 5, templete->GetY() - 5, selectedClass->GetX() + 5, templete->GetY() + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // 우상단
				CRect rect(templete->GetX() + templete->GetWidth() - 5, templete->GetY() - 5,
					templete->GetX() + templete->GetWidth() + 5, templete->GetY() + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // 좌하단
				CRect rect(selectedClass->GetX() - 5, selectedClass->GetY() + selectedClass->GetHeight() - 5,
					selectedClass->GetX() + 5, selectedClass->GetY() + selectedClass->GetHeight() + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // 우하단
				CRect rect(templete->GetX() + templete->GetWidth() - 5, selectedClass->GetY() + selectedClass->GetHeight() - 5,
					templete->GetX() + templete->GetWidth() + 5, selectedClass->GetY() + selectedClass->GetHeight() + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // 상중단
				CRect rect(selectedClass->GetX() + (templete->GetX() + templete->GetWidth() - selectedClass->GetX()) / 2 - 5, templete->GetY() - 5,
					selectedClass->GetX() + (templete->GetX() + templete->GetWidth() - selectedClass->GetX()) / 2 + 5, templete->GetY() + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // 하중단
				CRect rect(selectedClass->GetX() + (templete->GetX() + templete->GetWidth() - selectedClass->GetX()) / 2 - 5, selectedClass->GetY() + selectedClass->GetHeight() - 5,
					selectedClass->GetX() + (templete->GetX() + templete->GetWidth() - selectedClass->GetX()) / 2 + 5, selectedClass->GetY() + selectedClass->GetHeight() + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // 좌중단
				CRect rect(selectedClass->GetX() - 5, templete->GetY() + (selectedClass->GetY() + selectedClass->GetHeight() - templete->GetY()) / 2 - 5,
					selectedClass->GetX() + 5, templete->GetY() + (selectedClass->GetY() + selectedClass->GetHeight() - templete->GetY()) / 2 + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // 우중단
				CRect rect(templete->GetX() + templete->GetWidth() - 5, templete->GetY() + (selectedClass->GetY() + selectedClass->GetHeight() - templete->GetY()) / 2 - 5,
					templete->GetX() + templete->GetWidth() + 5, templete->GetY() + (selectedClass->GetY() + selectedClass->GetHeight() - templete->GetY()) / 2 + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
		}
		else {
			if (ret == false) { // 좌상단
				CRect rect(object->GetX() - 5, object->GetY() - 5, object->GetX() + 5, object->GetY() + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // 우상단
				CRect rect(object->GetX() + object->GetWidth() - 5, object->GetY() - 5, object->GetX() + object->GetWidth() + 5, object->GetY() + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // 좌하단
				CRect rect(object->GetX() - 5, object->GetY() + object->GetHeight() - 5, object->GetX() + 5, object->GetY() + object->GetHeight() + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // 우하단
				CRect rect(object->GetX() + object->GetWidth() - 5, object->GetY() + object->GetHeight() - 5,
					object->GetX() + object->GetWidth() + 5, object->GetY() + object->GetHeight() + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // 상중단
				CRect rect(object->GetX() + object->GetWidth() / 2 - 5, object->GetY() - 5, object->GetX() + object->GetWidth() / 2 + 5, object->GetY() + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // 하중단
				CRect rect(object->GetX() + object->GetWidth() / 2 - 5, object->GetY() + object->GetHeight() - 5,
					object->GetX() + object->GetWidth() / 2 + 5, object->GetY() + object->GetHeight() + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // 좌중단
				CRect rect(object->GetX() - 5, object->GetY() + object->GetHeight() / 2 - 5, object->GetX() + 5, object->GetY() + object->GetHeight() / 2 + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // 우중단
				CRect rect(object->GetX() + object->GetWidth() - 5, object->GetY() + object->GetHeight() / 2 - 5,
					object->GetX() + object->GetWidth() + 5, object->GetY() + object->GetHeight() / 2 + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
		}
	}
	if (ret == false) {
		Long distanceX = currentX - startX;
		Long distanceY = currentY - startY;
		Long i = 0;
		Long j;
		Figure *figure;
		while (i < length) {
			figure = selection->GetAt(i);
			if (dynamic_cast<FigureComposite*>(figure)) { //클래스나 메모면
														  // 해당 클래스나 메모 이동
				cPaintDc->Rectangle(figure->GetX() + distanceX, figure->GetY() + distanceY, figure->GetX() + figure->GetWidth() + distanceX,
					figure->GetY() + figure->GetHeight() + distanceY);
				FigureComposite *figureComposite = static_cast<FigureComposite*>(figure); // 형변환
				j = 0;
				while (j < figureComposite->GetLength()) { // 형변환 한게 관리하면 배열 렝스까지
					figure = figureComposite->GetAt(j);
					if (dynamic_cast<Line*>(figure)) {
						cPaintDc->MoveTo(figure->GetX() + distanceX, figure->GetY() + distanceY);
						cPaintDc->LineTo(figure->GetX() + figure->GetWidth() + distanceX,
							figure->GetY() + figure->GetHeight() + distanceY);
					}
					j++;
				}
			}
			i++;
		}
	}
	cPaintDc->SelectObject(oldPen);
	pen.DeleteObject();
}
Unclicked& Unclicked::operator=(const Unclicked& source) {
	return const_cast<Unclicked&>(source);
}