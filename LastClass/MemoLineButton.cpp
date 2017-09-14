//MemoLineButton.cpp

#include"MemoLineButton.h"
#include"DrawingController.h"


#include"Diagram.h"
#include"Selection.h"
#include "Class.h"
#include"MemoLine.h"
#include"MemoBox.h"

MemoLineButton::MemoLineButton() {

}

MemoLineButton::MemoLineButton(const MemoLineButton& source) {
	
}

MemoLineButton::~MemoLineButton() {

}

void MemoLineButton::ChangeState(DrawingController *drawingController, UINT nChar) {
	ButtonState::ChangeState(drawingController, nChar);
}

void MemoLineButton::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
	if (selection->GetLength() == 1 && dynamic_cast<FigureComposite*>(selection->GetAt(0))) {
		//Long endClass = this->diagram->Find(this->currentX, this->currentY);//�ڱ��ڽ� ����� 0 0 0 0 �� �����.. ������ 2017_09_09
		//Long x = this->currentX;
		//Long y = this->currentY;

		selection->FindByPoint(diagram, currentX, currentY);
		if(selection->GetLength() == 2 && selection->GetAt(0) != selection->GetAt(1) && (dynamic_cast<MemoBox*>(selection->GetAt(0)) || dynamic_cast<MemoBox*>(selection->GetAt(1)))) {
		//if (selection->GetLength() == 2 && selection->GetAt(0) != selection->GetAt(1)) {

			CPoint line1Start;
			CPoint line1End;
			CPoint line2Start;
			CPoint line2End;
			CPoint cross1;
			CPoint cross2;

			line1Start.x = startX;
			line1Start.y = startY;
			line1End.x = currentX;
			line1End.y = currentY;

			bool startClassCheck = false;
			if (startClassCheck == false) {//���� Ŭ�������� ���� �����ϴ� �� ã��
										   //���
				line2Start.x = selection->GetAt(0)->GetX();
				line2Start.y = selection->GetAt(0)->GetY();
				line2End.x = selection->GetAt(0)->GetX() + selection->GetAt(0)->GetWidth();
				line2End.y = selection->GetAt(0)->GetY();
				startClassCheck = selection->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross1);
			}
			if (startClassCheck == false) {
				//����
				line2Start.x = selection->GetAt(0)->GetX();
				line2Start.y = selection->GetAt(0)->GetY();
				line2End.x = selection->GetAt(0)->GetX();
				line2End.y = selection->GetAt(0)->GetY() + selection->GetAt(0)->GetHeight();
				startClassCheck = selection->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross1);
			}
			if (startClassCheck == false) {
				//����
				line2Start.x = selection->GetAt(0)->GetX() + selection->GetAt(0)->GetWidth();
				line2Start.y = selection->GetAt(0)->GetY();
				line2End.x = selection->GetAt(0)->GetX() + selection->GetAt(0)->GetWidth();
				line2End.y = selection->GetAt(0)->GetY() + selection->GetAt(0)->GetHeight();
				startClassCheck = selection->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross1);
			}
			if (startClassCheck == false) {
				//�ϴ�
				line2Start.x = selection->GetAt(0)->GetX();
				line2Start.y = selection->GetAt(0)->GetY() + selection->GetAt(0)->GetHeight();
				line2End.x = selection->GetAt(0)->GetX() + selection->GetAt(0)->GetWidth();
				line2End.y = selection->GetAt(0)->GetY() + selection->GetAt(0)->GetHeight();
				startClassCheck = selection->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross1);
			}

			bool endClassCheck = false;
			if (endClassCheck == false) {//�� Ŭ�������� ���� �����ϴ� �� ã��
										 //���
				line2Start.x = selection->GetAt(1)->GetX();
				line2Start.y = selection->GetAt(1)->GetY();
				line2End.x = selection->GetAt(1)->GetX() + selection->GetAt(1)->GetWidth();
				line2End.y = selection->GetAt(1)->GetY();
				endClassCheck = selection->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross2);
			}
			if (endClassCheck == false) {
				//����
				line2Start.x = selection->GetAt(1)->GetX();
				line2Start.y = selection->GetAt(1)->GetY();
				line2End.x = selection->GetAt(1)->GetX();
				line2End.y = selection->GetAt(1)->GetY() + selection->GetAt(1)->GetHeight();
				endClassCheck = selection->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross2);
			}
			if (endClassCheck == false) {
				//����
				line2Start.x = selection->GetAt(1)->GetX() + selection->GetAt(1)->GetWidth();
				line2Start.y = selection->GetAt(1)->GetY();
				line2End.x = selection->GetAt(1)->GetX() + selection->GetAt(1)->GetWidth();
				line2End.y = selection->GetAt(1)->GetY() + selection->GetAt(1)->GetHeight();
				endClassCheck = selection->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross2);
			}
			if (endClassCheck == false) {
				//�ϴ�
				line2Start.x = selection->GetAt(1)->GetX();
				line2Start.y = selection->GetAt(1)->GetY() + selection->GetAt(1)->GetHeight();
				line2End.x = selection->GetAt(1)->GetX() + selection->GetAt(1)->GetWidth();
				line2End.y = selection->GetAt(1)->GetY() + selection->GetAt(1)->GetHeight();
				endClassCheck = selection->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross2);
			}

			MemoLine object(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
			static_cast<FigureComposite*>(selection->GetAt(0))->Add(object.Clone());
		}
	}
}
void MemoLineButton::Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {

	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDc->SelectObject(&pen);
	cPaintDc->SetBkMode(TRANSPARENT);
	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(currentX, currentY);
	cPaintDc->SelectObject(oldPen);
	pen.DeleteObject();
}

MemoLineButton& MemoLineButton::operator=(const MemoLineButton& source) {
	return const_cast<MemoLineButton&>(source);
}