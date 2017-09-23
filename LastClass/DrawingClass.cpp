
#include "Diagram.h"
#include "Class.h"
#include "DrawingClass.h"
#include "DefaultState.h"
#include "Selection.h"


DrawingClass* DrawingClass::instance = 0;

MouseLButtonAction* DrawingClass::Instance() {
	if (instance == 0) {
		instance = new DrawingClass;
	}
	return instance;
}
void DrawingClass::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){

	//�������� �Ȱ�ġ�� �ҷ��� ���⿡ ����

	if (currentX - startX < 120) {
		currentX = startX + 120;
	}
	if (currentY - startY < 150) {
		currentY = startY + 150;
	}

	//Ŭ������ �Ȱ�ġ�� �ҷ��� ���⿡ ����
	Long index = diagram->AddClass(startX, startY, currentX - startX, currentY - startY);
	Class *object = static_cast<Class*>(diagram->GetAt(index));
	object->Initialize();
	this->ChangeDefault(mouseLButton);
}
void DrawingClass::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){

}
void DrawingClass::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPaintDC) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDC->SelectObject(&pen);
	cPaintDC->SetBkMode(TRANSPARENT);
	cPaintDC->Rectangle(startX, startY, currentX, currentY);
	cPaintDC->SelectObject(oldPen);
	pen.DeleteObject();
}