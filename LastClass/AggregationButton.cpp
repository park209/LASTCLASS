//AggregationButton.cpp

#include"AggregationButton.h"
#include"DrawingController.h"


#include"Diagram.h"
#include"Selection.h"
#include "SelfAggregation.h"
#include"Aggregation.h"
#include"Class.h"
#include"Finder.h"

AggregationButton::AggregationButton() {

}

AggregationButton::AggregationButton(const AggregationButton& source) {

}

AggregationButton::~AggregationButton() {

}

void AggregationButton::ChangeState(DrawingController *drawingController, UINT nChar) {
	ButtonState::ChangeState(drawingController, nChar);
}

Figure* AggregationButton::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
	Long index;
	Figure *figure = 0;

	if (selection->GetLength() == 1 && dynamic_cast<Class*>(selection->GetAt(0))) {

		selection->SelectByPoint(diagram, currentX, currentY);

		if (selection->GetLength() == 2 && selection->GetAt(0) != selection->GetAt(1) && dynamic_cast<Class*>(selection->GetAt(1))) {

			CPoint lineStart(startX, startY);
			CPoint lineEnd(currentX, currentY);

			CRect rect(selection->GetAt(0)->GetX(), selection->GetAt(0)->GetY(),
				selection->GetAt(0)->GetX() + selection->GetAt(0)->GetWidth(),
				selection->GetAt(0)->GetY() + selection->GetAt(0)->GetHeight());

			Finder finder;
			CPoint cross1 = finder.GetCrossPoint(lineStart, lineEnd, rect);

			rect.left = selection->GetAt(1)->GetX();
			rect.top = selection->GetAt(1)->GetY();
			rect.right = selection->GetAt(1)->GetX() + selection->GetAt(1)->GetWidth();
			rect.bottom = selection->GetAt(1)->GetY() + selection->GetAt(1)->GetHeight();
			CPoint cross2 = finder.GetCrossPoint(lineStart, lineEnd, rect);

			Aggregation object(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
			index = static_cast<FigureComposite*>(selection->GetAt(0))->Add(object.Clone());
			figure = static_cast<FigureComposite*>(selection->GetAt(0))->GetAt(index);
		}
		if (selection->GetLength() == 2 && selection->GetAt(0) == selection->GetAt(1)) {
			Class *object = static_cast<Class*>(selection->GetAt(0));
			SelfAggregation selfAggregation(object->GetX() + object->GetWidth() - 30, object->GetY(), 30, 30);
			index = object->Add(selfAggregation.Clone());
			figure = object->GetAt(index);
		}
	}

	return figure;
}
void AggregationButton::Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {
	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(currentX, currentY);

	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	double degree = atan2(currentX - startX, startY - currentY); // ����

	double distance = sqrt(pow(currentX - startX, 2) + pow(startY - currentY, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(
	double dX = (currentX) - (10 * (currentX - startX) / distance); //�ڷ� �� ������ x
	double dY = (currentY) + (10 * (startY - currentY) / distance); //�ڷ� �� ������ y

	//������� ȭ��ǥ �������� ������

	dX = (startX) + (10 * (currentX - startX) / distance); //�ڷ� �� ������ x
	dY = (startY) - (10 * (startY - currentY) / distance); //�ڷ� �� ������ y

	double dX2 = (startX) - ((currentX - startX) / distance);
	double dY2 = (startY) + ((startY - currentY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts2[0].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //���콺 ó�� ��
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts2[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(10 * (currentX - startX) / distance); // ����
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(10 * (startY - currentY) / distance);

	cPaintDc->SelectObject(&white);
	cPaintDc->Polygon(pts2, 4);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
AggregationButton& AggregationButton::operator=(const AggregationButton& source) {
	return const_cast<AggregationButton&>(source);
}