//AggregationsButton.cpp

#include"AggregationsButton.h"
#include"DrawingController.h"


#include"Diagram.h"
#include"Selection.h"

#include"Aggregations.h"
#include"Class.h"
#include"Finder.h"

AggregationsButton::AggregationsButton() {

}

AggregationsButton::AggregationsButton(const AggregationsButton& source) {

}

AggregationsButton::~AggregationsButton() {

}

void AggregationsButton::ChangeState(DrawingController *drawingController, UINT nChar) {
	ButtonState::ChangeState(drawingController, nChar);
}

Figure* AggregationsButton::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
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

			Aggregations object(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
			index = static_cast<FigureComposite*>(selection->GetAt(0))->Add(object.Clone());
			figure= static_cast<FigureComposite*>(selection->GetAt(0))->GetAt(index);
		}
	}
	return figure;
}
void AggregationsButton::Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {
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

	CPoint pts[3];

	pts[0].x = (currentX); //���콺 ������ġ ��
	pts[0].y = (currentY);

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // ����
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // �Ʒ���
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[1].x, pts[1].y);

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[2].x, pts[2].y);


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
AggregationsButton& AggregationsButton::operator=(const AggregationsButton& source) {
	return const_cast<AggregationsButton&>(source);
}