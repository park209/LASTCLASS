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

#include "MovingLineProcess.h"

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

	MovingLineProcess *moveLine = MovingLineProcess::Instance();

	if (selectedClass->GetAttributePosition() != -1) {
		if (distanceY < 0) { // up
			moveLine->MoveUpAttributeLine(selectedClass, startX, startY, currentX, currentY);
		}
		else { // down 
			moveLine->MoveDownAttributeLine(selectedClass, startX, startY, currentX, currentY);
		}
	}
	if (selectedClass->GetMethodPosition() != -1 && ret != true) {
		if (distanceY < 0) { // up
			moveLine->MoveUpMethodLine(selectedClass, startX, startY, currentX, currentY);
		}
		else { // 내릴때
			moveLine->MoveDownMethodLine(selectedClass, startX, startY, currentX, currentY);
		}
	}

	if (selectedClass->GetReceptionPosition() != -1 && ret != true) {
		if (distanceY < 0) {
			//올릴떄
			moveLine->MoveUpReception(selectedClass, startX, startY, currentX, currentY);
		}
		else {//내릴때
			moveLine->MoveDownReception(selectedClass, startX, startY, currentX, currentY);
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