#include "DrawingRelation.h"
#include "DefaultState.h"
#include "Figure.h"
#include "Selection.h"
#include "Class.h"
#include "Finder.h"
#include "Generalization.h"
#include "SelfGeneralization.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"

DrawingRelation* DrawingRelation::instance = 0;

MouseLButtonAction* DrawingRelation::Instance() {
	if (instance == 0) {
		instance = new DrawingRelation;
	}
	return instance;
}

//얘 누가 쓰는거지? 선도 그냥 일반화 만드는데 왜 있는건지 모르겠네

void DrawingRelation::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	//Long index;
	//Figure *figure = 0;

	//classDiagramForm->historyGraphic->PushUndo(diagram);
	//selection->SelectByPoint(diagram, currentX, currentY);

	//if (selection->GetLength() == 2 && dynamic_cast<Class*>(selection->GetAt(0)) && dynamic_cast<Class*>(selection->GetAt(1))
	//	&& selection->GetAt(0) != selection->GetAt(1)) {
	//	CPoint lineStart(startX, startY);
	//	CPoint lineEnd(currentX, currentY);

	//	CRect rect(selection->GetAt(0)->GetX(), selection->GetAt(0)->GetY(),
	//		selection->GetAt(0)->GetX() + selection->GetAt(0)->GetWidth(),
	//		selection->GetAt(0)->GetY() + selection->GetAt(0)->GetHeight());

	//	Finder finder;
	//	CPoint cross1 = finder.GetCrossPoint(lineStart, lineEnd, rect);

	//	rect.left = selection->GetAt(1)->GetX();
	//	rect.top = selection->GetAt(1)->GetY();
	//	rect.right = selection->GetAt(1)->GetX() + selection->GetAt(1)->GetWidth();
	//	rect.bottom = selection->GetAt(1)->GetY() + selection->GetAt(1)->GetHeight();
	//	CPoint cross2 = finder.GetCrossPoint(lineStart, lineEnd, rect);

	//	Generalization object(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
	//	index = static_cast<FigureComposite*>(selection->GetAt(0))->Add(object.Clone());
	//	figure = static_cast<FigureComposite*>(selection->GetAt(0))->GetAt(index);

	//}

	//else if (selection->GetLength() == 2 && dynamic_cast<Class*>(selection->GetAt(0)) && selection->GetAt(0) == selection->GetAt(1)) {
	//	Class *object = static_cast<Class*>(selection->GetAt(0));
	//	SelfGeneralization selfGeneralization(object->GetX() + object->GetWidth() - 30, object->GetY(), 30, 30);
	//	index = object->Add(selfGeneralization.Clone());
	//	figure = object->GetAt(index);
	//}

	selection->DeleteAllItems();
	this->ChangeDefault(mouseLButton);
}

void DrawingRelation::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){
	//selection->DeleteAllItems();
	//selection->SelectByPoint(diagram, currentX, currentY);
}

void DrawingRelation::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {
	//if (startX == currentX&&startY == currentY) {
	//	selection->DeleteAllItems();
	//	selection->SelectByPoint(diagram, currentX, currentY);
	//}
	//	CPen pen;
	//	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	//	CPen *oldPen = pDC->SelectObject(&pen);
	//	pDC->SetBkMode(TRANSPARENT);
	//	pDC->MoveTo(startX, startY);
	//	pDC->LineTo(currentX, currentY);
	//	pDC->SelectObject(oldPen);
	//	pen.DeleteObject();
}