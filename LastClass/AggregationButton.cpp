//AggregationButton.cpp

#include"AggregationButton.h"
#include"DrawingController.h"


#include"Diagram.h"
#include"Selection.h"

#include"Aggregation.h"
#include"Class.h"

AggregationButton::AggregationButton() {

}

AggregationButton::AggregationButton(const AggregationButton& source) {

}

AggregationButton::~AggregationButton() {

}

void AggregationButton::ChangeState(DrawingController *drawingController, UINT nChar) {
	ButtonState::ChangeState(drawingController, nChar);
}

void AggregationButton::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
	if (selection->GetLength() == 1 && dynamic_cast<Class*>(selection->GetAt(0))) {

		selection->FindByPoint(diagram, currentX, currentY);

		if (selection->GetLength() == 2 && selection->GetAt(0) != selection->GetAt(1) && dynamic_cast<Class*>(selection->GetAt(1))) {

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

			Aggregation object(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
			static_cast<FigureComposite*>(selection->GetAt(0))->Add(object.Clone());
		}
	}
}
void AggregationButton::Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {
	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(currentX, currentY);

	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	double degree = atan2(currentX - startX, startY - currentY); // ����

	double distance = sqrt(pow(currentX - startX, 2) + pow(startY - currentY, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(
	double dX = (currentX) - (15 * (currentX - startX) / distance); //�ڷ� �� ������ x
	double dY = (currentY) + (15 * (startY - currentY) / distance); //�ڷ� �� ������ y

	  // ���� ����

	//CPoint pts[3];

	//pts[0].x = (currentX); //���콺 ������ġ ��
	//pts[0].y = (currentY);

	//pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
	//pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	//pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
	//pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	//cPaintDc->MoveTo(pts[0].x, pts[0].y);
	//cPaintDc->LineTo(pts[1].x, pts[1].y);

	//cPaintDc->MoveTo(pts[0].x, pts[0].y);
	//cPaintDc->LineTo(pts[2].x, pts[2].y);


	//������� ȭ��ǥ �������� ������

	dX = (startX) + (15 * (currentX - startX) / distance); //�ڷ� �� ������ x
	dY = (startY) - (15 * (startY - currentY) / distance); //�ڷ� �� ������ y

	double dX2 = (startX) - ((currentX - startX) / distance);
	double dY2 = (startY) + ((startY - currentY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
	pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //���콺 ó�� ��
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
	pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (currentX - startX) / distance); // ����
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (startY - currentY) / distance);

	cPaintDc->SelectObject(&white);
	cPaintDc->Polygon(pts2, 4);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
AggregationButton& AggregationButton::operator=(const AggregationButton& source) {
	return const_cast<AggregationButton&>(source);
}