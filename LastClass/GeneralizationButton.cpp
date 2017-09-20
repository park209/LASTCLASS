//GeneralizationButton.cpp

#include"GeneralizationButton.h"
#include"DrawingController.h"

#include"ClassButton.h"
#include"Diagram.h"
#include"Selection.h"
#include"Generalization.h"
#include"Class.h"
#include"Finder.h"
#include"SelfGeneralization.h"

GeneralizationButton::GeneralizationButton() {

}

GeneralizationButton::GeneralizationButton(const GeneralizationButton& source) {

}

GeneralizationButton::~GeneralizationButton() {

}

void GeneralizationButton::ChangeState(DrawingController *drawingController, UINT nChar) {
	ButtonState::ChangeState(drawingController, nChar);
}

Figure* GeneralizationButton::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
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

			Generalization object(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
			index = static_cast<FigureComposite*>(selection->GetAt(0))->Add(object.Clone());
			figure = static_cast<FigureComposite*>(selection->GetAt(0))->GetAt(index);

		}

		if (selection->GetLength() == 2 && selection->GetAt(0) == selection->GetAt(1) ) {
			Class *object = static_cast<Class*>(selection->GetAt(0));
			SelfGeneralization selfGeneralization(object->GetX() + object->GetWidth() - 30, object->GetY(), 30, 30);
			index =object->Add(selfGeneralization.Clone());
			figure=object->GetAt(index);
		}
	}
	return figure;
}
void GeneralizationButton::Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {
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
	if (startX != currentX && startY != currentY) {
		cPaintDc->Polygon(pts, 3);
	}
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}
GeneralizationButton& GeneralizationButton::operator=(const GeneralizationButton& source) {
	return const_cast<GeneralizationButton&>(source);
}