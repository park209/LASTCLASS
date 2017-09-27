//MovingLine.cpp

#include "MovingLine.h"
#include "FigureComposite.h"
#include "Selection.h"
#include "Finder.h"
#include "Class.h"
#include "Template.h"
#include "SelectionState.h"

#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "Reception.h"

MovingLine* MovingLine::instance = 0;

MouseLButtonAction* MovingLine::Instance() {
	if (instance == 0) {
		instance = new MovingLine;
	}
	return instance;
}
void MovingLine::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	bool ret = false;
	Long distanceX = currentX - startX;
	Long distanceY = currentY - startY;
	Class *selectedClass = static_cast<Class*>(selection->GetAt(0));
	Finder finder;

	CPoint startPoint(0, 0);
	CPoint endPoint(0, 0);
	CRect rect{ startX - 4, startY - 4, startX + 4, startY + 4 };

	if (selectedClass->GetAttributePosition() != -1) {
		startPoint.x = selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetX();
		startPoint.y = selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetY();
		endPoint.x = selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetX() + selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetWidth();
		endPoint.y = selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetY();
		ret = finder.FindLineByArea(startPoint, endPoint, rect);
		if (ret == true) { // attribute Line
			if (distanceY < 0) { // up
				selectedClass->GetAt(0)->SetHeight(currentY - selectedClass->GetAt(0)->GetY());
				if (selectedClass->GetAt(0)->GetHeight() < 25) {
					selectedClass->GetAt(0)->SetHeight(25);
					distanceY = selectedClass->GetY() + selectedClass->GetAt(0)->GetHeight() - startPoint.y;
				}
				selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->Move(0, distanceY); // 선 이동

				selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(
					selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY() + selectedClass->GetAt(selectedClass->GetAttributePosition())->GetHeight() -
					selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetY());
				selectedClass->GetAt(selectedClass->GetAttributePosition())->SetY(
					selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetY());
			}
			else { // down 
				selectedClass->GetAt(selectedClass->GetAttributePosition())->SetY(selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY() + distanceY);
				selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(selectedClass->GetAt(selectedClass->GetAttributePosition())->GetHeight() - distanceY);
				selectedClass->GetAt(0)->SetHeight(selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY() - selectedClass->GetY());
				if (selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY() + selectedClass->GetAt(selectedClass->GetAttributePosition())->GetHeight() - 25<
					selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY()) {
					selectedClass->GetAt(selectedClass->GetAttributePosition())->SetY(selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY()
						+ selectedClass->GetAt(selectedClass->GetAttributePosition())->GetHeight() - 25);
					selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(25);
					//요거 위에거 헤이트를 (밑에거 겟X - 위에거 겟x)로 바꾸면됨
					selectedClass->GetAt(0)->SetHeight(selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY() - selectedClass->GetY());
					//
					distanceY = selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY() - startPoint.y;
				}
				selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->Move(0, distanceY); // 선 이동
			}
		}
	}
	if (selectedClass->GetMethodPosition() != -1 && ret != true) {
		startPoint.x = selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetX();
		startPoint.y = selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetY();
		endPoint.x = selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetX() + selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetWidth();
		endPoint.y = selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetY();
		ret = finder.FindLineByArea(startPoint, endPoint, rect);
		if (ret == true) { // method line
			if (distanceY < 0) { // up
				if (selectedClass->GetAttributePosition() != -1) { // attribute exist
					selectedClass->GetAt(selectedClass->GetAttributePosition())->
						SetHeight(currentY - selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY());
					if (selectedClass->GetAt(selectedClass->GetAttributePosition())->GetHeight() < 25) {
						selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(25);
						distanceY = selectedClass->GetY() + static_cast<Attribute*>(selectedClass->GetAt(selectedClass->GetAttributePosition() - 1))
							->GetHeight() - startPoint.y;
					}
				}
				else { // className exist
					selectedClass->GetAt(0)->SetHeight(currentY - selectedClass->GetAt(0)->GetY());
					if (selectedClass->GetAt(0)->GetHeight() < 25) {
						selectedClass->GetAt(0)->SetHeight(25);
						distanceY = selectedClass->GetY() + selectedClass->GetAt(0)->GetHeight() - startPoint.y;
					}
				}
				selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->Move(0, distanceY);
				selectedClass->GetAt(selectedClass->GetMethodPosition())->SetHeight(
					selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() + selectedClass->GetAt(selectedClass->GetMethodPosition())->GetHeight() -
					selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetY());
				selectedClass->GetAt(selectedClass->GetMethodPosition())->SetY(
					selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetY());
			}
			else {//내릴때
				if (selectedClass->GetAttributePosition() != -1) {
					selectedClass->GetAt(selectedClass->GetMethodPosition())->SetY(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() + distanceY);
					selectedClass->GetAt(selectedClass->GetMethodPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetHeight() - distanceY);
					selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() - selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY());
					if (selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() + selectedClass->GetAt(selectedClass->GetMethodPosition())->GetHeight() - 25<
						selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY()) {
						selectedClass->GetAt(selectedClass->GetMethodPosition())->SetY(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY()
							+ selectedClass->GetAt(selectedClass->GetMethodPosition())->GetHeight() - 25);
						selectedClass->GetAt(selectedClass->GetMethodPosition())->SetHeight(25);
						selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() - selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY());
						distanceY = selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() - startPoint.y;
					}
				}
				else {
					selectedClass->GetAt(selectedClass->GetMethodPosition())->SetY(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() + distanceY);
					selectedClass->GetAt(selectedClass->GetMethodPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetHeight() - distanceY);
					selectedClass->GetAt(0)->SetHeight(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() - selectedClass->GetY());
					if (selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() + selectedClass->GetAt(selectedClass->GetMethodPosition())->GetHeight() - 25<
						selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY()) {
						selectedClass->GetAt(selectedClass->GetMethodPosition())->SetY(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY()
							+ selectedClass->GetAt(selectedClass->GetMethodPosition())->GetHeight() - 25);
						selectedClass->GetAt(selectedClass->GetMethodPosition())->SetHeight(25);
						selectedClass->GetAt(0)->SetHeight(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() - selectedClass->GetY());
						distanceY = selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() - startPoint.y;
					}
				}
				selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->Move(0, distanceY);
			}
		}
	}

	if (selectedClass->GetReceptionPosition() != -1 && ret != true) {
		startPoint.x = selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetX();
		startPoint.y = selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetY();
		endPoint.x = selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetX() + selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetWidth();
		endPoint.y = selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetY();
		ret = finder.FindLineByArea(startPoint, endPoint, rect);
		if (ret == true) {
			if (distanceY < 0) {
				//올릴떄
				if (selectedClass->GetMethodPosition() != -1) {
					selectedClass->GetAt(selectedClass->GetMethodPosition())->
						SetHeight(currentY - selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY());
					if (selectedClass->GetAt(selectedClass->GetMethodPosition())->GetHeight() < 25) {
						selectedClass->GetAt(selectedClass->GetMethodPosition())->SetHeight(25);
						distanceY = selectedClass->GetY() + selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)
							->GetHeight() - startPoint.y;
					}
				}
				else {
					if (selectedClass->GetAttributePosition() != -1) {
						selectedClass->GetAt(selectedClass->GetAttributePosition())->
							SetHeight(currentY - selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY());
						if (selectedClass->GetAt(selectedClass->GetAttributePosition())->GetHeight() < 25) {
							selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(25);
							distanceY = selectedClass->GetY() + selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)
								->GetHeight() - startPoint.y;
						}
					}
					else {
						selectedClass->GetAt(0)->SetHeight(currentY - selectedClass->GetAt(0)->GetY());
						if (selectedClass->GetAt(0)->GetHeight() < 25) {
							selectedClass->GetAt(0)->SetHeight(25);
							distanceY = selectedClass->GetY() + selectedClass->GetAt(0)->GetHeight() - startPoint.y;
						}
					}
				}
				selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->Move(0, distanceY);
				selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetHeight(
					selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() + selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() -
					selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetY());
				selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetY(
					selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetY());
			}
			else {//내릴때
				if (selectedClass->GetMethodPosition() != -1) {
					selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetY(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() + distanceY);
					selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() - distanceY);
					selectedClass->GetAt(selectedClass->GetMethodPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY());
					if (selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() + selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() - 25<
						selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY()) {
						selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetY(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY()
							+ selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() - 25);
						selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetHeight(25);
						selectedClass->GetAt(selectedClass->GetMethodPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY());
						distanceY = selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - startPoint.y;
					}
				}

				else if (selectedClass->GetMethodPosition() == -1 && selectedClass->GetAttributePosition() != -1) {
					selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetY(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() + distanceY);
					selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() - distanceY);
					selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY());
					if (selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() + selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() - 25<
						selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY()) {
						selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetY(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY()
							+ selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() - 25);
						selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetHeight(25);
						selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY());
						distanceY = selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - startPoint.y;
					}
				}
				else if (selectedClass->GetMethodPosition() == -1 && selectedClass->GetAttributePosition() == -1) {
					selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetY(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() + distanceY);
					selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() - distanceY);
					selectedClass->GetAt(0)->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - selectedClass->GetY());
					if (selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() + selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() - 25<
						selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY()) {
						selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetY(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY()
							+ selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() - 25);
						selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetHeight(25);
						selectedClass->GetAt(0)->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - selectedClass->GetY());
						distanceY = selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - startPoint.y;
					}
				}
				selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->Move(0, distanceY);
			}
		}
	}
	this->ChangeState(mouseLButton, SelectionState::Instance());
}

void MovingLine::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

}

void MovingLine::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPaintDC) {
	bool ret = false;
	Long distanceX = currentX - startX;
	Long distanceY = currentY - startY;
	Class *selectedClass = static_cast<Class*>(selection->GetAt(0));
	Long x = selectedClass->GetX();
	Long y = selectedClass->GetY();
	Long width = selectedClass->GetWidth();
	Long height = selectedClass->GetHeight();
	CRect rect;
	Finder finder;

	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDC->SelectObject(&pen);
	cPaintDC->SetBkMode(TRANSPARENT);

	rect.left = startX - 4;
	rect.top = startY - 4;
	rect.right = startX + 4;
	rect.bottom = startY + 4;

	CPoint startPoint(0, 0);
	CPoint endPoint(0, 0);

	if (selectedClass->GetAttributePosition() != -1) {
		startPoint.x = selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetX();
		startPoint.y = selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetY();
		endPoint.x = selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetX() + selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetWidth();
		endPoint.y = selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetY();
		ret = finder.FindLineByArea(startPoint, endPoint, rect);
		if (ret == true) {

			cPaintDC->MoveTo(startPoint.x, startPoint.y + distanceY);
			cPaintDC->LineTo(endPoint.x, endPoint.y + distanceY);
		}
	}
	if (selectedClass->GetMethodPosition() != -1 && ret != true) {
		startPoint.x = selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetX();
		startPoint.y = selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetY();
		endPoint.x = selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetX() + selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetWidth();
		endPoint.y = selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetY();
		ret = finder.FindLineByArea(startPoint, endPoint, rect);
		if (ret == true) {
			cPaintDC->MoveTo(startPoint.x, startPoint.y + distanceY);
			cPaintDC->LineTo(endPoint.x, endPoint.y + distanceY);
		}
	}
	if (selectedClass->GetReceptionPosition() != -1 && ret != true) {
		startPoint.x = selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetX();
		startPoint.y = selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetY();
		endPoint.x = selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetX() + selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetWidth();
		endPoint.y = selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetY();
		ret = finder.FindLineByArea(startPoint, endPoint, rect);
		if (ret == true) {
			cPaintDC->MoveTo(startPoint.x, startPoint.y + distanceY);
			cPaintDC->LineTo(endPoint.x, endPoint.y + distanceY);
		}
	}
	cPaintDC->SelectObject(oldPen);
	pen.DeleteObject();
}