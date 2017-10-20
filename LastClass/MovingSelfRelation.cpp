//MovingSelfRelation.cpp
#include "MovingSelfRelation.h"
#include "SelfRelation.h"
#include "Figure.h"
#include "Diagram.h"
#include "Class.h"
#include "ClassDiagramForm.h"
#include "SelectionState.h"
#include "Selection.h"
#include "LastClass.h"
MovingSelfRelation* MovingSelfRelation::instance = 0;

MouseLButtonAction* MovingSelfRelation::Instance() {
	if (instance == 0) {
		instance = new MovingSelfRelation;
	}
	return instance;
}
void MovingSelfRelation::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

	SelfRelation *selfRelation = static_cast<SelfRelation*>(selection->GetAt(0));
	Long k = 0;
	Long l = 0;
	Long temp = -1;
	Class *object;

	while (k < diagram->GetLength() && temp == -1) {
		if (dynamic_cast<Class*>(diagram->GetAt(k))) {
			object = static_cast<Class*>(diagram->GetAt(k));
			l = 0;
			while (l < object->GetLength() && temp == -1) {
				if (dynamic_cast<SelfRelation*>(object->GetAt(l)) == selfRelation) {
					temp = k;
				}

				l++;
			}
		}
		k++;
	}
	if (temp != -1) {
		if (currentX < diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() / 2) {
			selfRelation->Modify(diagram->GetAt(temp)->GetX() + 30 * classDiagramForm->zoomRate / 100, diagram->GetAt(temp)->GetY(),
				-selfRelation->GetWidth(), -selfRelation->GetHeight());
		}
		else {
			if (dynamic_cast<Class*>(diagram->GetAt(temp))->GetTempletePosition() == -1) {
				selfRelation->Modify(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() - 30 * classDiagramForm->zoomRate / 100, diagram->GetAt(temp)->GetY(),
					selfRelation->GetWidth(), selfRelation->GetHeight());
			}
			else {
				selfRelation->Modify(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() - 30 * classDiagramForm->zoomRate / 100, diagram->GetAt(temp)->GetY() - classDiagramForm->seventeen,
					selfRelation->GetWidth(), selfRelation->GetHeight());
			}

		}
	}
	//selection->DeleteAllItems();
	//this->ChangeDefault(mouseLButton);
	this->ChangeState(mouseLButton, SelectionState::Instance());
}


void MovingSelfRelation::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

}
void MovingSelfRelation::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {

	LastClass *test = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);
	
	SelfRelation *selfRelation = static_cast<SelfRelation*>(selection->GetAt(0));
	Long k = 0;
	Long l = 0;
	Long temp = -1;
	Class *object;

	while (k < diagram->GetLength() && temp == -1) {
		if (dynamic_cast<Class*>(diagram->GetAt(k))) {
			object = static_cast<Class*>(diagram->GetAt(k));
			l = 0;
			while (l < object->GetLength() && temp == -1) {
				if (dynamic_cast<SelfRelation*>(object->GetAt(l)) == selfRelation) {
					temp = k;
				}

				l++;
			}
		}
		k++;
	}
	if (currentX < diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() / 2) {
		pDC->MoveTo(diagram->GetAt(temp)->GetX() + 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY());
		pDC->LineTo(diagram->GetAt(temp)->GetX() + 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
		pDC->MoveTo(diagram->GetAt(temp)->GetX() + 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
		pDC->LineTo(diagram->GetAt(temp)->GetX() - 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
		pDC->MoveTo(diagram->GetAt(temp)->GetX() - 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
		pDC->LineTo(diagram->GetAt(temp)->GetX() - 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
		pDC->MoveTo(diagram->GetAt(temp)->GetX() - 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
		pDC->LineTo(diagram->GetAt(temp)->GetX() , selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
	}
	else {
		if (dynamic_cast<Class*>(diagram->GetAt(temp))->GetTempletePosition() == -1) {
			pDC->MoveTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() - 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY());
			pDC->LineTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() - 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
			pDC->MoveTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() - 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
			pDC->LineTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() + 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
			pDC->MoveTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() + 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
			pDC->LineTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() + 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
			pDC->MoveTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() + 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
			pDC->LineTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() , selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
		}
		else {
			pDC->MoveTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() - 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 17 * test->classDiagramForm->zoomRate / 100);
			pDC->LineTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() - 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
			pDC->MoveTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() - 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
			pDC->LineTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() + 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
			pDC->MoveTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() + 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
			pDC->LineTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() + 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
			pDC->MoveTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() + 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
			pDC->LineTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth(), selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
		}

	}


	pDC->SelectObject(oldPen);
	pen.DeleteObject();

}