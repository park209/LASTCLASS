#include "DrawingDependency.h"
#include "DefaultState.h"
#include "Figure.h"
#include "Selection.h"
#include "Class.h"
#include "Finder.h"
#include "Dependency.h"
#include "SelfDependency.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "RollNameBox.h"
DrawingDependency* DrawingDependency::instance = 0;

MouseLButtonAction* DrawingDependency::Instance() {
	if (instance == 0) {
		instance = new DrawingDependency;
	}
	return instance;
}

void DrawingDependency::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	Long index;
	Figure *figure = 0;

	Long quadrant;
	Long quadrant2;

	classDiagramForm->historyGraphic->PushUndo(diagram, classDiagramForm->zoomRate);
	selection->SelectByPointForRelation(diagram, currentX, currentY);

	if (selection->GetLength() == 2 && dynamic_cast<Class*>(selection->GetAt(0)) && dynamic_cast<Class*>(selection->GetAt(1))
		&& selection->GetAt(0) != selection->GetAt(1)) {
		Class * classObject = dynamic_cast<Class*>(selection->GetAt(0));
		Class * classObject2 = dynamic_cast<Class*>(selection->GetAt(1));
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

		quadrant = finder.FindQuadrant(cross1.x, cross1.y, classObject->GetX(), classObject->GetY(),
			classObject->GetX() + classObject->GetWidth(), classObject->GetY() + classObject->GetHeight());

		quadrant2 = finder.FindQuadrant(cross2.x, cross2.y, classObject2->GetX(), classObject2->GetY(),
			classObject2->GetX() + classObject2->GetWidth(), classObject2->GetY() + classObject2->GetHeight());

		if (classObject->GetTempletePosition() != -1 && quadrant == 1
			&& cross1.x >= classObject->GetAt(classObject->GetTempletePosition())->GetX() - 10) {
			cross1.x = classObject->GetAt(classObject->GetTempletePosition())->GetX() - 10;
		}

		if (classObject2->GetTempletePosition() != -1 && quadrant2 == 1
			&& cross2.x >= classObject2->GetAt(classObject2->GetTempletePosition())->GetX() - 10) {
			cross2.x = classObject2->GetAt(classObject2->GetTempletePosition())->GetX() - 10;
		}

		Dependency object(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
		index = static_cast<FigureComposite*>(selection->GetAt(0))->Add(object.Clone());
		figure = static_cast<FigureComposite*>(selection->GetAt(0))->GetAt(index);
	}

	else if (selection->GetLength() == 2 && dynamic_cast<Class*>(selection->GetAt(0)) && selection->GetAt(0) == selection->GetAt(1)) {
		Class *object = static_cast<Class*>(selection->GetAt(0));
		Long i = 0;
		bool ret = false;
		while (i < object->GetLength()) {
			if (dynamic_cast<SelfRelation*>(object->GetAt(i))) {
				ret = true;
			}
			i++;
		}
		if (ret == false) {
			SelfDependency selfDependency(object->GetX() + object->GetWidth() - 30 * classDiagramForm->zoomRate / 100,
				object->GetY(), 30 * classDiagramForm->zoomRate / 100, 30 * classDiagramForm->zoomRate / 100);
			if (object->GetTempletePosition() != -1) {
				selfDependency.Move(0, -17);
				Long k = 0;
				while (k < 5) {
					CPoint cPoint(selfDependency.rollNamePoints->GetAt(k).x, selfDependency.rollNamePoints->GetAt(k).y - 17);
					selfDependency.rollNamePoints->Modify(k, cPoint);
					k++;
				}
			}
			index = object->Add(selfDependency.Clone());
			figure = object->GetAt(index);
		}
	}
	selection->DeleteAllItems();
	this->ChangeDefault(mouseLButton);
}
void DrawingDependency::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	selection->DeleteAllItems();
	selection->SelectByPoint(diagram, currentX, currentY);
}

void DrawingDependency::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {
	if (startX == currentX&&startY == currentY) {
		selection->DeleteAllItems();
		selection->SelectByPoint(diagram, currentX, currentY);
	}
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);
	pDC->MoveTo(startX, startY);
	pDC->LineTo(currentX, currentY);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();

	double degree = atan2(currentX - startX, startY - currentY); // ����

	double distance = sqrt(pow(currentX - startX, 2) + pow(startY - currentY, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(
	double dX = (currentX)-(10 * (currentX - startX) / distance); //�ڷ� �� ������ x
	double dY = (currentY)+(10 * (startY - currentY) / distance); //�ڷ� �� ������ y

																  // ���� ����

	CPoint pts[3];

	pts[0].x = (currentX); //���콺 ������ġ ��
	pts[0].y = (currentY);

	pts[1].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts[1].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[1].x, pts[1].y);

	pDC->MoveTo(pts[0].x, pts[0].y);
	pDC->LineTo(pts[2].x, pts[2].y);

}