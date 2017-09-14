//ClassButton.cpp

#include"ClassButton.h"
#include"Diagram.h"
#include"Class.h"
#include"DrawingController.h"
#include"ClassName.h"
#include"Attribute.h"
#include"Method.h"

ClassButton::ClassButton() {

}

ClassButton::ClassButton(const ClassButton& source) {

}

ClassButton::~ClassButton() {

}

void ClassButton::ChangeState(DrawingController *drawingController, UINT nChar) {
	ButtonState::ChangeState(drawingController, nChar);
}

Figure* ClassButton::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
	if (currentX - startX < 120) {
		currentX = startX + 120;
	}
	if (currentY - startY < 150) {
		currentY = startY + 150;
	}
	Long index = diagram->AddClass(startX, startY, currentX - startX, currentY - startY);

	//Class 생성자에서 Line 만드는거 추가에서 -> Class Add에서 Line 만드는거 추가에서 -> Form 마우스 드래그 끝날떄
	//끝나면서 Class 만든거에 Line 추가하는걸로 바꿈 2017.08.24

	//선 만듦
	//수정
	Class *tempClass = static_cast<Class*>(diagram->GetAt(index));
	tempClass->Add(startX, startY + 30,
		currentX - startX, startY + 30);
	tempClass->Add(startX, (startY + 30 + currentY) / 2,
		currentX - startX, (startY + 30 + currentY) / 2);
	ClassName className (startX + 5, startY + 33, currentX - startX - 10, 20, "11111");
	tempClass->Add(className.Clone());
	Attribute attribute(startX, startY + 50, currentX, (startY + 50 + currentY) / 2, "2222"); // 내용값은 수정해야함
	Method method(startX, (startY + 50 + currentY) / 2, currentX, currentY, "3333");
	tempClass->Add(attribute.Clone());
	tempClass->Add(method.Clone());

	return diagram->GetAt(index);
}
void ClassButton::Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDc->SelectObject(&pen);
	cPaintDc->SetBkMode(TRANSPARENT);
	cPaintDc->Rectangle(startX, startY, currentX, currentY);
	cPaintDc->SelectObject(oldPen);
	pen.DeleteObject();
}

ClassButton& ClassButton::operator=(const ClassButton& source) {
	return const_cast<ClassButton&>(source);
}