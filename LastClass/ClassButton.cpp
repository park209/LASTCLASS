//ClassButton.cpp

#include"ClassButton.h"
#include"Diagram.h"
#include"Class.h"
#include"DrawingController.h"


ClassButton::ClassButton() {

}

ClassButton::ClassButton(const ClassButton& source) {

}

ClassButton::~ClassButton() {

}

void ClassButton::ChangeState(DrawingController *drawingController, Long key) {
	ButtonState::ChangeState(drawingController, key);
}

void ClassButton::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
	if (currentX - startX < 120) {
		currentX = startX + 120;
	}
	if (currentY - startY < 150) {
		currentY = startY + 150;
	}
	Long index = diagram->AddClass(startX, startY, currentX - startX, currentY - startY);
	//Class �����ڿ��� Line ����°� �߰����� -> Class Add���� Line ����°� �߰����� -> Form ���콺 �巡�� ������
	//�����鼭 Class ����ſ� Line �߰��ϴ°ɷ� �ٲ� 2017.08.24

	//�� ����
	//����
	static_cast<Class*>(diagram->GetAt(index))->Add(startX, startY + 30,
		currentX - startX, startY + 30);
	static_cast<Class*>(diagram->GetAt(index))->Add(startX, (startY + 30 + currentY) / 2,
		currentX - startX, (startY + 30 + currentY) / 2);
}

ClassButton& ClassButton::operator=(const ClassButton& source) {
	return const_cast<ClassButton&>(source);
}