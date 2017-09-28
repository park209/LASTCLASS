//DrawRollNameBoxes.cpp

#include "DrawRollNameBoxes.h"
#include "RollNameBox.h"
#include "Relation.h"

DrawRollNameBoxes* DrawRollNameBoxes::instance = 0;

DrawRollNameBoxes* DrawRollNameBoxes::Instance() {
	if (instance == 0) {
		instance = new DrawRollNameBoxes;
	}
	return instance;
}

DrawRollNameBoxes::DrawRollNameBoxes() {
}

DrawRollNameBoxes::DrawRollNameBoxes(const DrawRollNameBoxes& source) {
}

DrawRollNameBoxes::~DrawRollNameBoxes() {
}


void DrawRollNameBoxes::DrawFirstRollNameBox(Relation *relationLine, CDC *cPaintDc) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint;

	CPoint startPoint{ relationLine->GetX(), relationLine->GetY() };
	CPoint endPoint{ relationLine->GetAt(0).x, relationLine->GetAt(0).y };
	cPoint = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
	cPaintDc->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);
}

void DrawRollNameBoxes::DrawSecondRollNameBox(Relation *relationLine, CDC *cPaintDc) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint;

	if (relationLine->GetLength() & 2 > 0) {
		CPoint startPoint2{ relationLine->GetAt((relationLine->GetLength() - 1) / 2).x,
			relationLine->GetAt((relationLine->GetLength() - 1) / 2).y };
		cPoint = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
		cPaintDc->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);
	}
	else {
		CPoint startPoint2{ relationLine->GetAt((relationLine->GetLength() - 1) / 2).x,
			relationLine->GetAt((relationLine->GetLength() - 1) / 2).y };
		CPoint endPoint2{ relationLine->GetAt((relationLine->GetLength() - 1) / 2 + 1).x,
			relationLine->GetAt((relationLine->GetLength() - 1) / 2 + 1).y };
		cPoint = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
		cPaintDc->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);
	}
}

void DrawRollNameBoxes::DrawThirdRollNameBox(Relation *relationLine, CDC *cPaintDc) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint;

	CPoint startPoint3{ relationLine->GetAt(relationLine->GetLength() - 1).x,
		relationLine->GetAt(relationLine->GetLength() - 1).y };
	CPoint endPoint3{ relationLine->GetX() + relationLine->GetWidth() , relationLine->GetY() + relationLine->GetHeight() };
	cPoint = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
	cPaintDc->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);
}

void DrawRollNameBoxes::DrawFourthRollNameBox(Relation *relationLine, CDC *cPaintDc) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint;

	CPoint startPoint{ relationLine->GetX(), relationLine->GetY() };
	CPoint endPoint{ relationLine->GetAt(0).x, relationLine->GetAt(0).y };
	cPoint = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
	cPaintDc->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);
}

void DrawRollNameBoxes::DrawFifthRollNameBox(Relation *relationLine, CDC *cPaintDc) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint;

	CPoint startPoint3{ relationLine->GetAt(relationLine->GetLength() - 1).x,
		relationLine->GetAt(relationLine->GetLength() - 1).y };
	CPoint endPoint3{ relationLine->GetX() + relationLine->GetWidth() , relationLine->GetY() + relationLine->GetHeight() };

	cPoint = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
	cPaintDc->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);
}

void DrawRollNameBoxes::DrawBoxesWithoutCurvedLine(Relation *relationLine, CDC *cPaintDc) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint;

	CPoint startPoint{ relationLine->GetX(), relationLine->GetY() };
	CPoint endPoint{ relationLine->GetX() + relationLine->GetWidth(),  relationLine->GetY() + relationLine->GetHeight() };
	cPoint = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
	cPaintDc->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);
	cPoint = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
	cPaintDc->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);
	cPoint = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
	cPaintDc->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);
	cPoint = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
	cPaintDc->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);
	cPoint = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
	cPaintDc->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);
}
