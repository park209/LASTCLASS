//DrawingVisitor.cpp

#include"DrawingVisitor.h"
#include "Diagram.h"
#include "Class.h"
#include "MemoBox.h"
#include "Selection.h"
#include "Template.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "Reception.h"
#include "Line.h"
#include "Generalization.h"
#include "Realization.h"
#include "Dependency.h"
#include "Association.h"
#include "DirectedAssociation.h"
#include "Aggregation.h"
#include "Aggregations.h"
#include "Composition.h"
#include "Compositions.h"
#include "MemoLine.h"
#include "SelfGeneralization.h"
#include "SelfDependency.h"
#include "SelfAggregation.h"
#include "SelfAssociation.h"
#include "SelfAggregations.h"
#include "SelfDirectedAssociation.h"
#include "SelfComposition.h"
#include "SelfCompositions.h"

#include <iostream>
using namespace std;

DrawingVisitor::DrawingVisitor() {
}
DrawingVisitor::~DrawingVisitor() {
}
void DrawingVisitor::Visit(Diagram *diagram, Selection *selection, Long distanceX, Long distanceY) {
}
void DrawingVisitor::Visit(Class *object, CDC* cPaintDc) {

	Long x = object->GetX();
	Long y = object->GetY();
	Long width = object->GetWidth();
	Long height = object->GetHeight();

	cPaintDc->Rectangle(x, y, x + width, y + height);
}
void DrawingVisitor::Visit(MemoBox *memoBox, CDC *cPaintDc) {
	Long x = memoBox->GetX();
	Long y = memoBox->GetY();;
	Long width = memoBox->GetWidth();
	Long height = memoBox->GetHeight();

	CPoint pts2[5];
	pts2[0].x = static_cast<LONG>(x + 15); // 윗점
	pts2[0].y = static_cast<LONG>(y);

	pts2[1].x = static_cast<LONG>(x); //마우스 처음 점
	pts2[1].y = static_cast<LONG>(y + 15);

	pts2[2].x = static_cast<LONG>(x); // 아랫점
	pts2[2].y = static_cast<LONG>(y + height);

	pts2[3].x = static_cast<LONG>(x + width); // 윗점
	pts2[3].y = static_cast<LONG>(y + height);

	pts2[4].x = static_cast<LONG>(x + width); // 윗점
	pts2[4].y = static_cast<LONG>(y);

	cPaintDc->Polygon(pts2, 5);

	cPaintDc->MoveTo(pts2[0].x, pts2[0].y);
	cPaintDc->LineTo(pts2[0].x, pts2[0].y + 15);

	cPaintDc->MoveTo(pts2[1].x, pts2[1].y);
	cPaintDc->LineTo(pts2[0].x, pts2[0].y + 15);
}
void DrawingVisitor::Visit(Selection *selection, CDC *cPaintDc) {
	Long i = 0;
	while (i < selection->GetLength()) {
		if (dynamic_cast<Class*>(selection->GetAt(i))) {
			Class *object = static_cast<Class*>(selection->GetAt(i));
			if (object->GetTempletePosition() == -1) {
				cPaintDc->Rectangle(
					object->GetX() - 5,
					object->GetY() - 5,
					object->GetX() + 5,
					object->GetY() + 5);
				cPaintDc->Rectangle(
					object->GetX() + object->GetWidth() - 5,
					object->GetY() - 5,
					object->GetX() + object->GetWidth() + 5,
					object->GetY() + 5);
				cPaintDc->Rectangle(
					object->GetX() - 5,
					object->GetY() + object->GetHeight() - 5,
					object->GetX() + 5,
					object->GetY() + object->GetHeight() + 5);
				cPaintDc->Rectangle(
					object->GetX() + object->GetWidth() - 5,
					object->GetY() + object->GetHeight() - 5,
					object->GetX() + object->GetWidth() + 5,
					object->GetY() + object->GetHeight() + 5);

			}
			else {
				Long j = 0;
				while (j < object->GetLength()) {
					if (dynamic_cast<Template*>(object->GetAt(j))) {
						Template *templete = static_cast<Template*>(object->GetAt(j));
						cPaintDc->Rectangle(
							object->GetX() - 5,
							templete->GetY() - 5,
							object->GetX() + 5,
							templete->GetY() + 5);
						cPaintDc->Rectangle(
							templete->GetX() + templete->GetWidth() - 5,
							templete->GetY() - 5,
							templete->GetX() + templete->GetWidth() + 5,
							templete->GetY() + 5);
						cPaintDc->Rectangle(
							object->GetX() - 5,
							object->GetY() + object->GetHeight() - 5,
							object->GetX() + 5,
							object->GetY() + object->GetHeight() + 5);
						cPaintDc->Rectangle(
							templete->GetX() + templete->GetWidth() - 5,
							object->GetY() + object->GetHeight() - 5,
							templete->GetX() + templete->GetWidth() + 5,
							object->GetY() + object->GetHeight() + 5);

					}
					j++;

				}

			}
		}

		if (dynamic_cast<MemoBox*>(selection->GetAt(i))) {
			MemoBox *memoBox = static_cast<MemoBox*>(selection->GetAt(i));
			cPaintDc->Rectangle(
				memoBox->GetX() - 5,
				memoBox->GetY() - 5,
				memoBox->GetX() + 5,
				memoBox->GetY() + 5);
			cPaintDc->Rectangle(
				memoBox->GetX() + memoBox->GetWidth() - 5,
				memoBox->GetY() - 5,
				memoBox->GetX() + memoBox->GetWidth() + 5,
				memoBox->GetY() + 5);
			cPaintDc->Rectangle(
				memoBox->GetX() - 5,
				memoBox->GetY() + memoBox->GetHeight() - 5,
				memoBox->GetX() + 5,
				memoBox->GetY() + memoBox->GetHeight() + 5);
			cPaintDc->Rectangle(
				memoBox->GetX() + memoBox->GetWidth() - 5,
				memoBox->GetY() + memoBox->GetHeight() - 5,
				memoBox->GetX() + memoBox->GetWidth() + 5,
				memoBox->GetY() + memoBox->GetHeight() + 5);


		}
		Long j = 0;
		//상태패턴이던 뭐든 적용해야함
		if (dynamic_cast<Relation*>(selection->GetAt(i))) {
			if (static_cast<Relation*>(selection->GetAt(i))->GetLength() == 0) {
				cPaintDc->Rectangle(selection->GetAt(i)->GetX() - 5,
					selection->GetAt(i)->GetY() - 5,
					selection->GetAt(i)->GetX() + 5,
					selection->GetAt(i)->GetY() + 5);
				cPaintDc->Rectangle(selection->GetAt(i)->GetX() + (selection->GetAt(i)->GetWidth() / 2) - 5,
					selection->GetAt(i)->GetY() + (selection->GetAt(i)->GetHeight() / 2) - 5,
					selection->GetAt(i)->GetX() + (selection->GetAt(i)->GetWidth() / 2) + 5,
					selection->GetAt(i)->GetY() + (selection->GetAt(i)->GetHeight() / 2) + 5);
				cPaintDc->Rectangle(selection->GetAt(i)->GetX() + selection->GetAt(i)->GetWidth() - 5,
					selection->GetAt(i)->GetY() + selection->GetAt(i)->GetHeight() - 5,
					selection->GetAt(i)->GetX() + selection->GetAt(i)->GetWidth() + 5,
					selection->GetAt(i)->GetY() + selection->GetAt(i)->GetHeight() + 5);
			}
			else {
				cPaintDc->Rectangle(selection->GetAt(i)->GetX() - 5,
					selection->GetAt(i)->GetY() - 5,
					selection->GetAt(i)->GetX() + 5,
					selection->GetAt(i)->GetY() + 5);
				cPaintDc->Rectangle(selection->GetAt(i)->GetX() + selection->GetAt(i)->GetWidth() - 5,
					selection->GetAt(i)->GetY() + selection->GetAt(i)->GetHeight() - 5,
					selection->GetAt(i)->GetX() + selection->GetAt(i)->GetWidth() + 5,
					selection->GetAt(i)->GetY() + selection->GetAt(i)->GetHeight() + 5);
				while (j < dynamic_cast<Relation*>(selection->GetAt(i))->GetLength()) {
					CPoint cPoint = dynamic_cast<Relation*>(selection->GetAt(i))->GetAt(j);
					cPaintDc->Rectangle(cPoint.x - 5,
						cPoint.y - 5,
						cPoint.x + 5,
						cPoint.y + 5);
					j++;
				}
			}
		}
		if (dynamic_cast<SelfRelation*>(selection->GetAt(i))) {
			SelfRelation *selfRelation = static_cast<SelfRelation*>(selection->GetAt(i));
			Long x;
			Long y;
			Long x1;
			Long y1;

			x = selfRelation->GetX() - 5;
			y = selfRelation->GetY() - 35;
			x1 = selfRelation->GetX() + 5;
			y1 = selfRelation->GetY() - 25;
			cPaintDc->Rectangle(x, y, x1, y1);

			x = selfRelation->GetX() + 55;
			y = selfRelation->GetY() - 35;
			x1 = selfRelation->GetX() + 65;
			y1 = selfRelation->GetY() - 25;
			cPaintDc->Rectangle(x, y, x1, y1);

			x = selfRelation->GetX() + 55;
			y = selfRelation->GetY() + 25;
			x1 = selfRelation->GetX() + 65;
			y1 = selfRelation->GetY() + 35;
			cPaintDc->Rectangle(x, y, x1, y1);
		}
		i++;
	}

}
void DrawingVisitor::Visit(Template *object, CDC *cPaintDc) {
	Long x = object->GetX();
	Long  y = object->GetY();;
	Long width = object->GetWidth();
	Long height = object->GetHeight();

	cPaintDc->Rectangle(x, y, x + width, y + height);
}
void DrawingVisitor::Visit(ClassName* className, CDC* cPaintDc) {
}
void DrawingVisitor::Visit(Attribute* attribute, CDC* cPaintDc) {
}
void DrawingVisitor::Visit(Method* method, CDC* cPaintDc) {
}
void DrawingVisitor::Visit(Reception* reception, CDC* cPaintDc) {
}
void DrawingVisitor::Visit(Line *line, CDC* cPaintDc) {
	Long x = line->GetX();
	Long  y = line->GetY();;
	Long width = line->GetWidth();

	cPaintDc->MoveTo(x, y);
	cPaintDc->LineTo(x + width, y);
}
void DrawingVisitor::Visit(Generalization *generalization, CDC* cPaintDc) {

	Long startX = generalization->GetX();
	Long startY = generalization->GetY();
	Long endX = generalization->GetWidth() + generalization->GetX();
	Long endY = generalization->GetHeight() + generalization->GetY();
	//cout << "일반화출력" << " " << x << " " << y << " " << width << " " << height <<  endl;

	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);

	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y

														  // 수직 기울기

	CPoint pts[3];

	pts[0].x = (endX); //마우스 현재위치 점
	pts[0].y = (endY);

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->SelectObject(&white);
	cPaintDc->Polygon(pts, 3);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(Realization *realization, CDC* cPaintDc) {

	Long startX = realization->GetX();
	Long  startY = realization->GetY();
	Long endX = realization->GetWidth() + realization->GetX();
	Long endY = realization->GetHeight() + realization->GetY();
	//cout << "실체화출력" << " " << x << " " << y << " " << width << " " << height << endl;

	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDc->SelectObject(&pen);
	cPaintDc->SetBkMode(TRANSPARENT);
	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);
	cPaintDc->SelectObject(oldPen);
	pen.DeleteObject();

	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y

														  // 수직 기울기

	CPoint pts[3];

	pts[0].x = endX; //마우스 현재위치 점
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->SelectObject(&white);
	cPaintDc->Polygon(pts, 3);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(Dependency *dependency, CDC* cPaintDc) {

	Long startX = dependency->GetX();
	Long  startY = dependency->GetY();
	Long endX = dependency->GetWidth() + dependency->GetX();
	Long endY = dependency->GetHeight() + dependency->GetY();
	//cout << "의존 출력" << " " << x << " " << y << " " << width << " " << height << endl;

	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDc->SelectObject(&pen);
	cPaintDc->SetBkMode(TRANSPARENT);
	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);
	cPaintDc->SelectObject(oldPen);
	pen.DeleteObject();

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y

														  // 수직 기울기

	CPoint pts[3];

	pts[0].x = endX; //마우스 현재위치 점
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[1].x, pts[1].y);

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[2].x, pts[2].y);
}
void DrawingVisitor::Visit(Association *association, CDC* cPaintDc) { //, CDC* cPaintDc

	Long startX = association->GetX();
	Long startY = association->GetY();
	Long endX = association->GetWidth() + association->GetX();
	Long endY = association->GetHeight() + association->GetY();
	//cout << "연관화출력" << " " << startX << " " << startY << " " << endX << " " << endY << endl;

	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);
}
void DrawingVisitor::Visit(DirectedAssociation *directedAssociation, CDC* cPaintDc) {

	Long startX = directedAssociation->GetX();
	Long  startY = directedAssociation->GetY();
	Long endX = directedAssociation->GetWidth() + directedAssociation->GetX();
	Long endY = directedAssociation->GetHeight() + directedAssociation->GetY();
	//cout << "직접연관출력" << " " << x << " " << y << " " << width << " " << height << endl;

	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y

														  // 수직 기울기

	CPoint pts[3];

	pts[0].x = endX; //마우스 현재위치 점
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[1].x, pts[1].y);

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[2].x, pts[2].y);
}
void DrawingVisitor::Visit(Aggregation *aggregation, CDC* cPaintDc) {

	Long  startX = aggregation->GetX();
	Long  startY = aggregation->GetY();
	Long endX = aggregation->GetWidth() + aggregation->GetX();
	Long endY = aggregation->GetHeight() + aggregation->GetY();
	//cout << "집합출력" << " " << x << " " << y << " " << width << " " << height << endl;

	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);

	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));

	double dX = (startX)+(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (startY)-(15 * (startY - endY) / distance); //뒤로 온 기준점 y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (endX - startX) / distance); // 윗점
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (startY - endY) / distance);

	cPaintDc->SelectObject(&white);
	cPaintDc->Polygon(pts2, 4);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(Aggregations *aggregations, CDC* cPaintDc) {

	Long startX = aggregations->GetX();
	Long  startY = aggregations->GetY();
	Long endX = aggregations->GetWidth() + aggregations->GetX();
	Long endY = aggregations->GetHeight() + aggregations->GetY();
	//cout << "집합연관출력" << " " << x << " " << y << " " << width << " " << height << endl;

	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);

	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y

														  // 수직 기울기

	CPoint pts[3];

	pts[0].x = endX; //마우스 현재위치 점
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[1].x, pts[1].y);

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[2].x, pts[2].y);


	//여기까지 화살표 다음부터 마름모

	dX = (startX)+(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	dY = (startY)-(15 * (startY - endY) / distance); //뒤로 온 기준점 y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (endX - startX) / distance); // 윗점
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (startY - endY) / distance);

	cPaintDc->SelectObject(&white);
	cPaintDc->Polygon(pts2, 4);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(Composition *composition, CDC* cPaintDc) {

	Long startX = composition->GetX();
	Long  startY = composition->GetY();
	Long endX = composition->GetWidth() + composition->GetX();
	Long endY = composition->GetHeight() + composition->GetY();
	//cout << "합성출력" << " " << x << " " << y << " " << width << " " << height << endl;

	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);

	CBrush black(RGB(000, 000, 000));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);


	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));

	double dX = (startX)+(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (startY)-(15 * (startY - endY) / distance); //뒤로 온 기준점 y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (endX - startX) / distance); // 윗점
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (startY - endY) / distance);

	cPaintDc->SelectObject(&black);
	cPaintDc->Polygon(pts2, 4);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(Compositions *compositions, CDC* cPaintDc) {

	Long startX = compositions->GetX();
	Long  startY = compositions->GetY();
	Long endX = compositions->GetWidth() + compositions->GetX();
	Long endY = compositions->GetHeight() + compositions->GetY();
	//cout << "복합연관출력" << " " << x << " " << y << " " << width << " " << height << endl;

	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);

	CBrush black(RGB(000, 000, 000));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	double degree = atan2(endX - startX, startY - endY); // 기울기


	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y

														  // 수직 기울기
	CPoint pts[3];

	pts[0].x = endX; //마우스 현재위치 점
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[1].x, pts[1].y);

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[2].x, pts[2].y);

	//여기까지 화살표 다음부터 마름모
	distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));

	dX = (startX)+(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	dY = (startY)-(15 * (startY - endY) / distance); //뒤로 온 기준점 y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(16 * (endX - startX) / distance); // 윗점
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(16 * (startY - endY) / distance);

	cPaintDc->SelectObject(&black);
	cPaintDc->Polygon(pts2, 4);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(MemoLine *memoLine, CDC *cPaintDc) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDc->SelectObject(&pen);
	cPaintDc->SetBkMode(TRANSPARENT);

	Long startX = memoLine->GetX();
	Long startY = memoLine->GetY();
	Long endX;
	Long endY;
	Long i = 0;

	while (i < memoLine->GetLength()) {
		endX = memoLine->GetAt(i).x;
		endY = memoLine->GetAt(i).y;
		cPaintDc->MoveTo(startX, startY);
		cPaintDc->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}
	endX = memoLine->GetWidth() + memoLine->GetX();
	endY = memoLine->GetHeight() + memoLine->GetY();

	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);

	cPaintDc->SelectObject(oldPen);
	pen.DeleteObject();
}
void DrawingVisitor::Visit(SelfGeneralization *selfGeneralization, CDC *cPaintDc) {

	cPaintDc->MoveTo(selfGeneralization->GetX(), selfGeneralization->GetY());
	cPaintDc->LineTo(selfGeneralization->GetX(), selfGeneralization->GetY() - 30);

	cPaintDc->MoveTo(selfGeneralization->GetX(), selfGeneralization->GetY() - 30);
	cPaintDc->LineTo(selfGeneralization->GetX() + 60, selfGeneralization->GetY() - 30);

	cPaintDc->MoveTo(selfGeneralization->GetX() + 60, selfGeneralization->GetY() - 30);
	cPaintDc->LineTo(selfGeneralization->GetX() + 60, selfGeneralization->GetY() + 30);

	cPaintDc->MoveTo(selfGeneralization->GetX() + 60, selfGeneralization->GetY() + 30);
	cPaintDc->LineTo(selfGeneralization->GetX() + 30, selfGeneralization->GetY() + 30);

	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	Long startX = selfGeneralization->GetX() + 60;
	Long startY = selfGeneralization->GetY() + 30;
	Long endX = selfGeneralization->GetX() + 30;
	Long endY = selfGeneralization->GetY() + 30;

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y
														  // 수직 기울기
	CPoint pts[3];

	pts[0].x = (endX); //마우스 현재위치 점
	pts[0].y = (endY);

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->SelectObject(&white);
	cPaintDc->Polygon(pts, 3);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(SelfDependency *selfDependency, CDC *cPaintDc) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDc->SelectObject(&pen);
	cPaintDc->SetBkMode(TRANSPARENT);

	cPaintDc->MoveTo(selfDependency->GetX(), selfDependency->GetY());
	cPaintDc->LineTo(selfDependency->GetX(), selfDependency->GetY() - 30);

	cPaintDc->MoveTo(selfDependency->GetX(), selfDependency->GetY() - 30);
	cPaintDc->LineTo(selfDependency->GetX() + 60, selfDependency->GetY() - 30);

	cPaintDc->MoveTo(selfDependency->GetX() + 60, selfDependency->GetY() - 30);
	cPaintDc->LineTo(selfDependency->GetX() + 60, selfDependency->GetY() + 30);

	cPaintDc->MoveTo(selfDependency->GetX() + 60, selfDependency->GetY() + 30);
	cPaintDc->LineTo(selfDependency->GetX() + 30, selfDependency->GetY() + 30);

	Long startX = selfDependency->GetX() + 60;
	Long startY = selfDependency->GetY() + 30;
	Long endX = selfDependency->GetX() + 30;
	Long endY = selfDependency->GetY() + 30;

	cPaintDc->SelectObject(oldPen);
	pen.DeleteObject();

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y
	// 수직 기울기
	CPoint pts[3];

	pts[0].x = endX; //마우스 현재위치 점
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[1].x, pts[1].y);

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[2].x, pts[2].y);
}
void DrawingVisitor::Visit(SelfAggregation *selfAggregation, CDC *cPaintDc) {
	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	cPaintDc->MoveTo(selfAggregation->GetX(), selfAggregation->GetY());
	cPaintDc->LineTo(selfAggregation->GetX(), selfAggregation->GetY() - 30);

	cPaintDc->MoveTo(selfAggregation->GetX(), selfAggregation->GetY() - 30);
	cPaintDc->LineTo(selfAggregation->GetX() + 60, selfAggregation->GetY() - 30);

	cPaintDc->MoveTo(selfAggregation->GetX() + 60, selfAggregation->GetY() - 30);
	cPaintDc->LineTo(selfAggregation->GetX() + 60, selfAggregation->GetY() + 30);

	cPaintDc->MoveTo(selfAggregation->GetX() + 60, selfAggregation->GetY() + 30);
	cPaintDc->LineTo(selfAggregation->GetX() + 30, selfAggregation->GetY() + 30);

	Long startX = selfAggregation->GetX() + 60;
	Long startY = selfAggregation->GetY() + 30;
	Long endX = selfAggregation->GetX() + 30;
	Long endY = selfAggregation->GetY() + 30;

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));

	double dX = (startX)+(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (startY)-(15 * (startY - endY) / distance); //뒤로 온 기준점 y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (endX - startX) / distance); // 윗점
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (startY - endY) / distance);

	cPaintDc->SelectObject(&white);
	cPaintDc->Polygon(pts2, 4);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(SelfAssociation *selfAssociation, CDC *cPaintDc) {

	cPaintDc->MoveTo(selfAssociation->GetX(), selfAssociation->GetY());
	cPaintDc->LineTo(selfAssociation->GetX(), selfAssociation->GetY() - 30);

	cPaintDc->MoveTo(selfAssociation->GetX(), selfAssociation->GetY() - 30);
	cPaintDc->LineTo(selfAssociation->GetX() + 60, selfAssociation->GetY() - 30);

	cPaintDc->MoveTo(selfAssociation->GetX() + 60, selfAssociation->GetY() - 30);
	cPaintDc->LineTo(selfAssociation->GetX() + 60, selfAssociation->GetY() + 30);

	cPaintDc->MoveTo(selfAssociation->GetX() + 60, selfAssociation->GetY() + 30);
	cPaintDc->LineTo(selfAssociation->GetX() + 30, selfAssociation->GetY() + 30);
}
void DrawingVisitor::Visit(SelfAggregations *selfAggregations, CDC *cPaintDc) {
	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	cPaintDc->MoveTo(selfAggregations->GetX(), selfAggregations->GetY());
	cPaintDc->LineTo(selfAggregations->GetX(), selfAggregations->GetY() - 30);

	cPaintDc->MoveTo(selfAggregations->GetX(), selfAggregations->GetY() - 30);
	cPaintDc->LineTo(selfAggregations->GetX() + 60, selfAggregations->GetY() - 30);

	cPaintDc->MoveTo(selfAggregations->GetX() + 60, selfAggregations->GetY() - 30);
	cPaintDc->LineTo(selfAggregations->GetX() + 60, selfAggregations->GetY() + 30);

	cPaintDc->MoveTo(selfAggregations->GetX() + 60, selfAggregations->GetY() + 30);
	cPaintDc->LineTo(selfAggregations->GetX() + 30, selfAggregations->GetY() + 30);

	Long startX = selfAggregations->GetX() + 60;
	Long startY = selfAggregations->GetY() + 30;
	Long endX = selfAggregations->GetX() + 30;
	Long endY = selfAggregations->GetY() + 30;

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y
	// 수직 기울기
	CPoint pts[3];

	pts[0].x = endX; //마우스 현재위치 점
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[1].x, pts[1].y);

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[2].x, pts[2].y);
	//여기까지 화살표 다음부터 마름모
	//문제
	startX = selfAggregations->GetX();
	startY = selfAggregations->GetY();
	endX = selfAggregations->GetWidth();
	endY = selfAggregations->GetHeight();

	degree = atan2(endX - startX, startY - endY);
	distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	dX = (startX)+(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	dY = (startY)-(15 * (startY - endY) / distance); //뒤로 온 기준점 y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];
	//작 성 자:구 보 승
	pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts2[1].x = static_cast<LONG>(startX); //마우스 처음 점
	pts2[1].y = static_cast<LONG>(startY);

	pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (endX - startX) / distance); // 윗점
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (startY - endY) / distance);

	cPaintDc->SelectObject(&white);
	cPaintDc->Polygon(pts2, 4);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(SelfDirectedAssociation *selfDirectedAssociation, CDC *cPaintDc) {
	cPaintDc->MoveTo(selfDirectedAssociation->GetX(), selfDirectedAssociation->GetY());
	cPaintDc->LineTo(selfDirectedAssociation->GetX(), selfDirectedAssociation->GetY() - 30);

	cPaintDc->MoveTo(selfDirectedAssociation->GetX(), selfDirectedAssociation->GetY() - 30);
	cPaintDc->LineTo(selfDirectedAssociation->GetX() + 60, selfDirectedAssociation->GetY() - 30);

	cPaintDc->MoveTo(selfDirectedAssociation->GetX() + 60, selfDirectedAssociation->GetY() - 30);
	cPaintDc->LineTo(selfDirectedAssociation->GetX() + 60, selfDirectedAssociation->GetY() + 30);

	cPaintDc->MoveTo(selfDirectedAssociation->GetX() + 60, selfDirectedAssociation->GetY() + 30);
	cPaintDc->LineTo(selfDirectedAssociation->GetX() + 30, selfDirectedAssociation->GetY() + 30);

	Long startX = selfDirectedAssociation->GetX() + 60;
	Long startY = selfDirectedAssociation->GetY() + 30;
	Long endX = selfDirectedAssociation->GetX() + 30;
	Long endY = selfDirectedAssociation->GetY() + 30;

	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y
	// 수직 기울기
	CPoint pts[3];

	pts[0].x = endX; //마우스 현재위치 점
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[1].x, pts[1].y);

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[2].x, pts[2].y);
}
void DrawingVisitor::Visit(SelfComposition *selfComposition, CDC *cPaintDc) {

	CBrush black(RGB(000, 000, 000));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	cPaintDc->MoveTo(selfComposition->GetX(), selfComposition->GetY());
	cPaintDc->LineTo(selfComposition->GetX(), selfComposition->GetY() - 30);

	cPaintDc->MoveTo(selfComposition->GetX(), selfComposition->GetY() - 30);
	cPaintDc->LineTo(selfComposition->GetX() + 60, selfComposition->GetY() - 30);

	cPaintDc->MoveTo(selfComposition->GetX() + 60, selfComposition->GetY() - 30);
	cPaintDc->LineTo(selfComposition->GetX() + 60, selfComposition->GetY() + 30);

	cPaintDc->MoveTo(selfComposition->GetX() + 60, selfComposition->GetY() + 30);
	cPaintDc->LineTo(selfComposition->GetX() + 30, selfComposition->GetY() + 30);

	Long startX = selfComposition->GetX() + 60;
	Long startY = selfComposition->GetY() + 30;
	Long endX = selfComposition->GetX() + 30;
	Long endY = selfComposition->GetY() + 30;

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));

	double dX = (startX)+(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (startY)-(15 * (startY - endY) / distance); //뒤로 온 기준점 y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (endX - startX) / distance); // 윗점
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (startY - endY) / distance);

	cPaintDc->SelectObject(&black);
	cPaintDc->Polygon(pts2, 4);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}

void DrawingVisitor::Visit(SelfCompositions *selfCompositions, CDC *cPaintDc) {
	CBrush black(RGB(000, 000, 000));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	cPaintDc->MoveTo(selfCompositions->GetX(), selfCompositions->GetY());
	cPaintDc->LineTo(selfCompositions->GetX(), selfCompositions->GetY() - 30);

	cPaintDc->MoveTo(selfCompositions->GetX(), selfCompositions->GetY() - 30);
	cPaintDc->LineTo(selfCompositions->GetX() + 60, selfCompositions->GetY() - 30);

	cPaintDc->MoveTo(selfCompositions->GetX() + 60, selfCompositions->GetY() - 30);
	cPaintDc->LineTo(selfCompositions->GetX() + 60, selfCompositions->GetY() + 30);

	cPaintDc->MoveTo(selfCompositions->GetX() + 60, selfCompositions->GetY() + 30);
	cPaintDc->LineTo(selfCompositions->GetX() + 30, selfCompositions->GetY() + 30);

	Long startX = selfCompositions->GetX() + 60;
	Long startY = selfCompositions->GetY() + 30;
	Long endX = selfCompositions->GetX() + 30;
	Long endY = selfCompositions->GetY() + 30;

	double degree = atan2(endX - startX, startY - endY); // 기울기


	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y
	// 수직 기울기
	CPoint pts[3];
	pts[0].x = endX; //마우스 현재위치 점
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[1].x, pts[1].y);

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[2].x, pts[2].y);
	//여기까지 화살표 다음부터 마름모
	startX = selfCompositions->GetX();
	startY = selfCompositions->GetY();

	degree = atan2(endX - startX, startY - endY);
	distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	dX = (startX)+(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	dY = (startY)-(15 * (startY - endY) / distance); //뒤로 온 기준점 y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];
	//작 성 자:구 보 승
	pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts2[1].x = static_cast<LONG>(startX); //마우스 처음 점
	pts2[1].y = static_cast<LONG>(startY);

	pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (endX - startX) / distance); // 윗점
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (startY - endY) / distance);

	cPaintDc->SelectObject(&black);
	cPaintDc->Polygon(pts2, 4);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
void DrawingVisitor::Visit(Text* text, CDC* cPaintDc) {
}