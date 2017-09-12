//ClassButton.cpp

#include"ClassButton.h"
#include"Diagram.h"
#include"Class.h"
#include"DrawingController.h"
#include"Unclicked.h"
#include"GeneralizationButton.h"
#include"RealizationButton.h"

ClassButton::ClassButton() {

}

ClassButton::ClassButton(const ClassButton& source) {

}

ClassButton::~ClassButton() {

}

void ClassButton::ChangeState(DrawingController *drawingController, Long key) {
	if (key == 0) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new Unclicked;
	}
	if (key == 1) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new ClassButton;
	}
	if (key == 2) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new GeneralizationButton;
	}
	if (key == 3) {
		if (drawingController->buttonState != 0) {
			delete drawingController->buttonState;
		}
		drawingController->buttonState = new RealizationButton;
	}
}

void ClassButton::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
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
	static_cast<Class*>(diagram->GetAt(index))->Add(startX, startY + 30,
		currentX - startX, startY + 30);
	static_cast<Class*>(diagram->GetAt(index))->Add(startX, (startY + 30 + currentY) / 2,
		currentX - startX, (startY + 30 + currentY) / 2);
}

ClassButton& ClassButton::operator=(const ClassButton& source) {
	return const_cast<ClassButton&>(source);
}