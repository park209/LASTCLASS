//Unclicked.cpp

#include"Unclicked.h"
#include"DrawingController.h"
#include "Selection.h"
#include "Line.h"
#include"Relation.h"
#include "Finder.h"
#include"Class.h"
#include"Template.h"
#include"Diagram.h"
#include"SelfRelation.h"
#include"Reception.h"

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
		FigureComposite *object = static_cast<FigureComposite*>(selection->GetAt(0));
		bool ret = false;
		Long x = object->GetX();
		Long y = object->GetY();
		Long width = object->GetWidth();
		Long height = object->GetHeight();
		Long distanceX = currentX - startX;
		Long distanceY = currentY - startY;
		Long i = 0;
		Figure *(*figures) = new Figure*[32];
		Finder finder;
		Long length=0;
		Long k = 0;
		Long Quadrant;
		if (ret == false) { // �»��
			CRect rect(object->GetX() - 3, object->GetY() - 3, object->GetX() + 6, object->GetY() + 6);
			ret = finder.FindRectangleByPoint(rect, startX, startY);

		}
		if (ret == false) { // ����
			CRect rect(object->GetX() + object->GetWidth() - 6, object->GetY() - 3, object->GetX() + object->GetWidth() + 3, object->GetY() + 6);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
		}
		if (ret == false) { // ���ϴ�
			CRect rect(object->GetX() - 3, object->GetY() + object->GetHeight() - 6, object->GetX() + 6, object->GetY() + object->GetHeight() + 3);
			ret = finder.FindRectangleByPoint(rect, startX, startY);

		}
		if (ret == false) { // ���ϴ�
			CRect rect(object->GetX() + object->GetWidth() - 6, object->GetY() + object->GetHeight() - 6,
				object->GetX() + object->GetWidth() + 3, object->GetY() + object->GetHeight() + 3);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {//���� ��������
				if (object->GetWidth() + distanceX < 120) {
					distanceX = 120 - object->GetWidth();
				}
				if (object->GetHeight() + distanceY < 150) {
					distanceY = 150 - object->GetHeight();
				}
				
				
			    //���輱
						//����
						finder.FindRelationEndPoints(diagram, object, figures, &length);
						while (k < length) {
							Quadrant = finder.FindQuadrant(figures[k]->GetX() + figures[k]->GetWidth(), figures[k]->GetY() + figures[k]->GetHeight(),
								object->GetX(), object->GetY(), object->GetX() + object->GetWidth(), object->GetY() + object->GetHeight());
							if (Quadrant == 1) {
								if (object->GetX() + object->GetWidth() + distanceX <= object->GetX() + 120) {
									figures[k]->EndPointMove(object->GetX() + 120 - (figures[k]->GetX() + figures[k]->GetWidth()), 0);
								}
								else {
									figures[k]->EndPointMove(distanceX, 0);
								}
							}
							else if (Quadrant == 2) {
								figures[k]->EndPointMove(distanceX, distanceY);
							}
							else if (Quadrant == 3) {
								figures[k]->EndPointMove(distanceX, distanceY);
							}
							else if (Quadrant == 4) {
								if (object->GetY() + object->GetHeight() + distanceY <= object->GetY() + 150) {
									figures[k]->EndPointMove(0, object->GetY() + 150 - (figures[k]->GetY() + figures[k]->GetHeight()));
								}
								else {
									figures[k]->EndPointMove(0, distanceY);
								}
							}
							k++;
						}
						//������
						i = 0;//�Ұ�1. �����̼� ������, 2 ���α����ذ��� �����ϱ�, 3. ������ ���� �ذ��ϱ�
						while (i<object->GetLength()) {
							if (dynamic_cast<Template*>(object->GetAt(i))) {
								object->GetAt(i)->Modify(object->GetAt(i)->GetX(), object->GetAt(i)->GetY(),
									object->GetAt(i)->GetWidth() + distanceX, object->GetAt(i)->GetHeight());
							}
							else if (dynamic_cast<SelfRelation*>(object->GetAt(i))) {
								object->GetAt(i)->Modify(object->GetAt(i)->GetX()+distanceX, object->GetAt(i)->GetY(), 0,0);
							}//�������
							else if (dynamic_cast<Relation*>(object->GetAt(i))) {

							}
							else if (dynamic_cast<Line*>(object->GetAt(i))) {
								object->GetAt(i)->Modify(object->GetAt(i)->GetX(), object->GetAt(i)->GetY(), 
									object->GetAt(i)->GetWidth() + distanceX, 0);
							}
							else {
								object->GetAt(i)->Modify(object->GetAt(i)->GetX(), object->GetAt(i)->GetY(), object->GetAt(i)->GetWidth() + distanceX, object->GetAt(i)->GetHeight() + distanceY);
							}
							i++;
					}
					
					

				 //
				 

				object->Modify(object->GetX(), object->GetY(), object->GetWidth() + distanceX, object->GetHeight() + distanceY);
				
				
			

				//if (dynamic_cast<FigureComposite*>(figure)) { //Ŭ������ �޸��
				//	Long startX = figure->GetX();
				//	Long startY = figure->GetY();
				//	Long endX = figure->GetX() + figure->GetWidth();
				//	Long endY = figure->GetY() + figure->GetHeight();
				//	figure->Move(distanceX, distanceY); // �ش� Ŭ������ �޸� �̵�
				//	FigureComposite *figureComposite = static_cast<FigureComposite*>(figure); // ����ȯ
				//	j = 0;
				//	while (j < figureComposite->GetLength()) { // ����ȯ �Ѱ� �����ϸ� �迭 ��������
				//		figure = figureComposite->GetAt(j);
				//		figure->Move(distanceX, distanceY);
				//		j++;
				//	}
				//	k = 0;
				//	while (k < diagram->GetLength()) {
				//		figureComposite = static_cast<FigureComposite*>(diagram->GetAt(k));
				//		l = 0;
				//		while (l < figureComposite->GetLength()) {
				//			if (dynamic_cast<Relation*>(figureComposite->GetAt(l))) {
				//				figure = figureComposite->GetAt(l);
				//				Long relationEndX = figure->GetX() + figure->GetWidth();
				//				Long relationEndY = figure->GetY() + figure->GetHeight();
				//				if (startX <= relationEndX &&  relationEndX <= endX &&
				//					startY <= relationEndY &&  relationEndY <= endY) {
				//					figure->EndPointMove(distanceX, distanceY);
				//				}
				//			}
				//			l++;
				//		}
				//		k++;
				//	}

				//}





			}
		}
		if (ret == false) { // ���ߴ�
			CRect rect(object->GetX() + object->GetWidth() / 2 - 4, object->GetY() - 3, object->GetX() + object->GetWidth() / 2 + 5, object->GetY() + 6);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
		}
		if (ret == false) { // ���ߴ�
			CRect rect(object->GetX() + object->GetWidth() / 2 - 4, object->GetY() + object->GetHeight() - 6,
				object->GetX() + object->GetWidth() / 2 + 5, object->GetY() + object->GetHeight() + 3);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
		}
		if (ret == false) { // ���ߴ�
			CRect rect(object->GetX() - 3, object->GetY() + object->GetHeight() / 2 - 4, object->GetX() + 6, object->GetY() + object->GetHeight() / 2 + 5);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
		}
		if (ret == false) { // ���ߴ�
			CRect rect(object->GetX() + object->GetWidth() - 6, object->GetY() + object->GetHeight() / 2 - 4,
				object->GetX() + object->GetWidth() + 3, object->GetY() + object->GetHeight() / 2 + 5);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
		}
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
		//CRect rect;
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
			if (ret == false) { // �»��
				CRect rect(selectedClass->GetX() - 3, templete->GetY() - 3, selectedClass->GetX() + 6, templete->GetY() + 6);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // ����
				CRect rect(templete->GetX() + templete->GetWidth() - 6, templete->GetY() - 3,
					templete->GetX() + templete->GetWidth() + 3, templete->GetY() + 6);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // ���ϴ�
				CRect rect(selectedClass->GetX() - 3, selectedClass->GetY() + selectedClass->GetHeight() - 6,
					selectedClass->GetX() + 6, selectedClass->GetY() + selectedClass->GetHeight() + 3);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // ���ϴ�
				CRect rect(templete->GetX() + templete->GetWidth() - 6, selectedClass->GetY() + selectedClass->GetHeight() - 6,
					templete->GetX() + templete->GetWidth() + 3, selectedClass->GetY() + selectedClass->GetHeight() + 3);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // ���ߴ�
				CRect rect(selectedClass->GetX() + (templete->GetX() + templete->GetWidth() - selectedClass->GetX()) / 2 - 4, templete->GetY() - 3,
					selectedClass->GetX() + (templete->GetX() + templete->GetWidth() - selectedClass->GetX()) / 2 + 5, templete->GetY() + 6);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // ���ߴ�
				CRect rect(selectedClass->GetX() + (templete->GetX() + templete->GetWidth() - selectedClass->GetX()) / 2 - 4, selectedClass->GetY() + selectedClass->GetHeight() - 6,
					selectedClass->GetX() + (templete->GetX() + templete->GetWidth() - selectedClass->GetX()) / 2 + 5, selectedClass->GetY() + selectedClass->GetHeight() + 3);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // ���ߴ�
				CRect rect(selectedClass->GetX() - 3, templete->GetY() + (selectedClass->GetY() + selectedClass->GetHeight() - templete->GetY()) / 2 - 4,
					selectedClass->GetX() + 5, templete->GetY() + (selectedClass->GetY() + selectedClass->GetHeight() - templete->GetY()) / 2 + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // ���ߴ�
				CRect rect(templete->GetX() + templete->GetWidth() - 6, templete->GetY() + (selectedClass->GetY() + selectedClass->GetHeight() - templete->GetY()) / 2 - 4,
					templete->GetX() + templete->GetWidth() + 3, templete->GetY() + (selectedClass->GetY() + selectedClass->GetHeight() - templete->GetY()) / 2 + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
		}
		else {
			if (ret == false) { // �»��
				CRect rect(object->GetX() - 3, object->GetY() - 3, object->GetX() + 6, object->GetY() + 6);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // ����
				CRect rect(object->GetX() + object->GetWidth() - 6, object->GetY() - 3, object->GetX() + object->GetWidth() + 3, object->GetY() + 6);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // ���ϴ�
				CRect rect(object->GetX() - 3, object->GetY() + object->GetHeight() - 6, object->GetX() + 6, object->GetY() + object->GetHeight() + 3);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // ���ϴ�
				CRect rect(object->GetX() + object->GetWidth() - 6, object->GetY() + object->GetHeight() - 6,
					object->GetX() + object->GetWidth() + 3, object->GetY() + object->GetHeight() + 3);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
				if (ret == true) {
					cPaintDc->Rectangle(object->GetX(), object->GetY(), object->GetX()+ object->GetWidth() + (currentX - startX),
						object->GetY()+object->GetHeight() + (currentY - startY));//������
				}
			}
			if (ret == false) { // ���ߴ�
				CRect rect(object->GetX() + object->GetWidth() / 2 - 4, object->GetY() - 3, object->GetX() + object->GetWidth() / 2 + 5, object->GetY() + 6);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // ���ߴ�
				CRect rect(object->GetX() + object->GetWidth() / 2 - 4, object->GetY() + object->GetHeight() - 6,
					object->GetX() + object->GetWidth() / 2 + 5, object->GetY() + object->GetHeight() + 3);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // ���ߴ�
				CRect rect(object->GetX() - 3, object->GetY() + object->GetHeight() / 2 - 4, object->GetX() + 6, object->GetY() + object->GetHeight() / 2 + 5);
				ret = finder.FindRectangleByPoint(rect, startX, startY);
			}
			if (ret == false) { // ���ߴ�
				CRect rect(object->GetX() + object->GetWidth() - 6, object->GetY() + object->GetHeight() / 2 - 4,
					object->GetX() + object->GetWidth() + 3, object->GetY() + object->GetHeight() / 2 + 5);
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
			if (dynamic_cast<FigureComposite*>(figure)) { //Ŭ������ �޸��
														  // �ش� Ŭ������ �޸� �̵�
				cPaintDc->Rectangle(figure->GetX() + distanceX, figure->GetY() + distanceY, figure->GetX() + figure->GetWidth() + distanceX,
					figure->GetY() + figure->GetHeight() + distanceY);
				FigureComposite *figureComposite = static_cast<FigureComposite*>(figure); // ����ȯ
				j = 0;
				while (j < figureComposite->GetLength()) { // ����ȯ �Ѱ� �����ϸ� �迭 ��������
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