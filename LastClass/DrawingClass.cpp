#include "ClassButton.h"
#include "Diagram.h"
#include "Class.h"
#include "DrawingClass.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "Figure.h"
DrawingClass* DrawingClass::instance = 0;

MouseLButtonAction* DrawingClass::Instance() {
	if (instance == 0) {
		instance = new DrawingClass;
	}
	return instance;
}
void DrawingClass::MouseLButtonUp(Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	if (currentX - startX < 120) {
		currentX = startX + 120;
	}
	if (currentY - startY < 150) {
		currentY = startY + 150;
	}
	Long index = diagram->AddClass(startX, startY, currentX - startX, currentY - startY);

	Class *object = static_cast<Class*>(diagram->GetAt(index));
	object->Initialize();

}
void DrawingClass::MouseLButtonDown(Long startX, Long startY, Long currentX, Long currentY, CPaintDC *cPatinDC) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPatinDC->SelectObject(&pen);
	cPatinDC->SetBkMode(TRANSPARENT);
	cPatinDC->Rectangle(startX, startY, currentX, currentY);
	cPatinDC->SelectObject(oldPen);
	pen.DeleteObject();
}