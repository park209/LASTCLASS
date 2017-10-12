
#include "Diagram.h"
#include "Class.h"
#include "DrawingClass.h"
#include "DefaultState.h"
#include "Selection.h"
#include "Finder.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "LastClass.h"
#include "StatusBar.h"

DrawingClass* DrawingClass::instance = 0;

MouseLButtonAction* DrawingClass::Instance() {
	if (instance == 0) {
		instance = new DrawingClass;
	}
	return instance;
}
void DrawingClass::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

	classDiagramForm->historyGraphic->PushUndo(diagram);

	CRect rect = diagram->GetCorrectRect(startX, startY, currentX, currentY);

	if (rect.Width() < 120) {
		rect.right = rect.left + 120;
	}
	if (rect.Height() < 150) {
		rect.bottom = rect.top + 150;
	}

	//클래스를 안겹치게 할려면 여기에 정의
	Long i = 0;
	Finder finder;
	bool ret = false;
	while (i < diagram->GetLength() && ret == false) {
		FigureComposite *figures = static_cast<FigureComposite*>(diagram->GetAt(i));
		CRect cRect1(figures->GetX(), figures->GetY(), figures->GetWidth() + figures->GetX(), figures->GetY() + figures->GetHeight());
		ret = finder.FindRectangleByArea(rect, cRect1);
		i++;
	}

	if (ret == false) {
		Long index = diagram->AddClass(rect.left, rect.top, rect.Width(), rect.Height());
		Class *object = static_cast<Class*>(diagram->GetAt(index));
		object->Initialize();
	}

	classDiagramForm->lastClass->statusBar->DestroyStatus();
	classDiagramForm->lastClass->statusBar->MakeStatusBar(classDiagramForm->lastClass, classDiagramForm->lastClass->GetSafeHwnd(), 0, 0, 5);

	this->ChangeDefault(mouseLButton);
}

void DrawingClass::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){
	selection->DeleteAllItems();
	
}

void DrawingClass::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);
	pDC->Rectangle(startX, startY, currentX, currentY);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}