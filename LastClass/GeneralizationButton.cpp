//GeneralizationButton.cpp

#include"GeneralizationButton.h"
#include"DrawingController.h"

#include"ClassButton.h"
#include"Diagram.h"
#include"Selection.h"
#include"Generalization.h"
#include"Class.h"


GeneralizationButton::GeneralizationButton() {

}

GeneralizationButton::GeneralizationButton(const GeneralizationButton& source) {

}

GeneralizationButton::~GeneralizationButton() {

}

void GeneralizationButton::ChangeState(DrawingController *drawingController, Long key) {
	ButtonState::ChangeState(drawingController, key);
}

void GeneralizationButton::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
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
			if (startClassCheck == false) {//시작 클래스에서 선과 교차하는 면 찾기
										   //상단
				line2Start.x = selection->GetAt(0)->GetX();
				line2Start.y = selection->GetAt(0)->GetY();
				line2End.x = selection->GetAt(0)->GetX() + selection->GetAt(0)->GetWidth();
				line2End.y = selection->GetAt(0)->GetY();
				startClassCheck = selection->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross1);
			}
			if (startClassCheck == false) {
				//좌측
				line2Start.x = selection->GetAt(0)->GetX();
				line2Start.y = selection->GetAt(0)->GetY();
				line2End.x = selection->GetAt(0)->GetX();
				line2End.y = selection->GetAt(0)->GetY() + selection->GetAt(0)->GetHeight();
				startClassCheck = selection->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross1);
			}
			if (startClassCheck == false) {
				//우측
				line2Start.x = selection->GetAt(0)->GetX() + selection->GetAt(0)->GetWidth();
				line2Start.y = selection->GetAt(0)->GetY();
				line2End.x = selection->GetAt(0)->GetX() + selection->GetAt(0)->GetWidth();
				line2End.y = selection->GetAt(0)->GetY() + selection->GetAt(0)->GetHeight();
				startClassCheck = selection->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross1);
			}
			if (startClassCheck == false) {
				//하단
				line2Start.x = selection->GetAt(0)->GetX();
				line2Start.y = selection->GetAt(0)->GetY() + selection->GetAt(0)->GetHeight();
				line2End.x = selection->GetAt(0)->GetX() + selection->GetAt(0)->GetWidth();
				line2End.y = selection->GetAt(0)->GetY() + selection->GetAt(0)->GetHeight();
				startClassCheck = selection->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross1);
			}

			bool endClassCheck = false;
			if (endClassCheck == false) {//끝 클래스에서 선과 교차하는 면 찾기
										 //상단
				line2Start.x = selection->GetAt(1)->GetX();
				line2Start.y = selection->GetAt(1)->GetY();
				line2End.x = selection->GetAt(1)->GetX() + selection->GetAt(1)->GetWidth();
				line2End.y = selection->GetAt(1)->GetY();
				endClassCheck = selection->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross2);
			}
			if (endClassCheck == false) {
				//좌측
				line2Start.x = selection->GetAt(1)->GetX();
				line2Start.y = selection->GetAt(1)->GetY();
				line2End.x = selection->GetAt(1)->GetX();
				line2End.y = selection->GetAt(1)->GetY() + selection->GetAt(1)->GetHeight();
				endClassCheck = selection->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross2);
			}
			if (endClassCheck == false) {
				//우측
				line2Start.x = selection->GetAt(1)->GetX() + selection->GetAt(1)->GetWidth();
				line2Start.y = selection->GetAt(1)->GetY();
				line2End.x = selection->GetAt(1)->GetX() + selection->GetAt(1)->GetWidth();
				line2End.y = selection->GetAt(1)->GetY() + selection->GetAt(1)->GetHeight();
				endClassCheck = selection->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross2);
			}
			if (endClassCheck == false) {
				//하단
				line2Start.x = selection->GetAt(1)->GetX();
				line2Start.y = selection->GetAt(1)->GetY() + selection->GetAt(1)->GetHeight();
				line2End.x = selection->GetAt(1)->GetX() + selection->GetAt(1)->GetWidth();
				line2End.y = selection->GetAt(1)->GetY() + selection->GetAt(1)->GetHeight();
				endClassCheck = selection->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross2);
			}

			Generalization object(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
			static_cast<FigureComposite*>(selection->GetAt(0))->Add(object.Clone());
		}
	}
}
void GeneralizationButton::Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {
	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(currentX, currentY);

	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	double degree = atan2(currentX - startX, startY - currentY); // 기울기

	double distance = sqrt(pow(currentX - startX, 2) + pow(startY - currentY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (currentX) - (15 * (currentX - startX) / distance); //뒤로 온 기준점 x
	double dY = (currentY) + (15 * (startY - currentY) / distance); //뒤로 온 기준점 y

																					  // 수직 기울기

	CPoint pts[3];

	pts[0].x = (currentX); //마우스 현재위치 점
	pts[0].y = (currentY);

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->SelectObject(&white);
	cPaintDc->Polygon(pts, 3);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
GeneralizationButton& GeneralizationButton::operator=(const GeneralizationButton& source) {
	return const_cast<GeneralizationButton&>(source);
}