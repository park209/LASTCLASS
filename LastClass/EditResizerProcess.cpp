//EditResizerProcess.cpp

#include "EditResizerProcess.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Figure.h"
#include "FigureComposite.h"
#include "Diagram.h"
#include "Finder.h"
#include "Selection.h"
#include "Relation.h"
#include "FigureComposite.h"
#include "MemoBox.h"
#include "Class.h"
#include "ClassName.h"
#include "Template.h"
#include "RollNameBox.h"

using namespace std;

EditResizerProcess::EditResizerProcess() {

}
EditResizerProcess::EditResizerProcess(const EditResizerProcess& source) {

}
EditResizerProcess::~EditResizerProcess() {

}
void EditResizerProcess::ResizeEditWidth(TextEdit *textEdit, CDC *cdc) {
	RECT rt;
	textEdit->GetClientRect(&rt);
	textEdit->SetWindowPos(&textEdit->wndTopMost, 0, 0,
		textEdit->text->MaxWidth(cdc) + CaretWidth, rt.bottom, SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOCOPYBITS);
}

void EditResizerProcess::ResizeEditHeight(TextEdit *textEdit, CDC *cdc) {
	RECT rt;
	textEdit->GetClientRect(&rt);
	textEdit->SetWindowPos(&textEdit->wndTopMost, 0, 0,
		rt.right, textEdit->GetRowHeight()*textEdit->text->GetLength(), SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOCOPYBITS);
}

void EditResizerProcess::ResizeEditAll(TextEdit *textEdit, CDC *cdc) {
	textEdit->SetWindowPos(&textEdit->wndTopMost, 0, 0,
		textEdit->text->MaxWidth(cdc) + CaretWidth, textEdit->GetRowHeight()*textEdit->text->GetLength() , SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOCOPYBITS);
}

void EditResizerProcess::RewindEdit(TextEdit *textEdit, CDC *cdc) {
	Long gabY_ = GabY * 2;
	if (dynamic_cast<MemoBox*>(textEdit->figure) || dynamic_cast<ClassName*>(textEdit->figure)) {
		gabY_ += MemoGab;
	}
	textEdit->SetWindowPos(&textEdit->wndTopMost,0, 0,
		textEdit->GetCriteriaWidth() - GabX *2, textEdit->GetCriteriaHeight() - gabY_, SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOCOPYBITS);
	if (dynamic_cast<Template*>(textEdit->figure)) {
		textEdit->SetWindowPos(&textEdit->wndTopMost,
			textEdit->GetCriteriaX()+GabX,
			textEdit->figure->GetY() + GabY,
			textEdit->GetCriteriaWidth() - GabX * 2,
			textEdit->GetCriteriaHeight() - gabY_,
			SWP_NOZORDER | SWP_NOREDRAW | SWP_NOCOPYBITS);
	}
}

void EditResizerProcess::ResizeClassWidth(TextEdit *textEdit) {
	RECT rt;
	textEdit->GetClientRect(&rt);
	FigureComposite *object = static_cast<FigureComposite*>(textEdit->classDiagramForm->selection->GetAt(0));
	Long distanceX;
	if (rt.right + GabX * 2 > textEdit->GetCriteriaWidth()) {
		distanceX = object->GetMinimumWidth() - object->GetWidth();
	}
	else {
		distanceX = textEdit->GetCriteriaWidth() - object->GetWidth();
	}
	object->ModifyComponetsToRightDirection(textEdit->classDiagramForm->diagram, distanceX);
}

void EditResizerProcess::ResizeClassHeight(TextEdit *textEdit) {
	RECT rt;
	textEdit->GetClientRect(&rt);

	Long gabY_ = GabY * 2;
	if (dynamic_cast<MemoBox*>(textEdit->figure) || dynamic_cast<ClassName*>(textEdit->figure)) {
		gabY_ += MemoGab;
	}
	Long distanceY;
	if (rt.bottom + gabY_ > textEdit->GetCriteriaHeight()) {
		distanceY = rt.bottom + gabY_ - textEdit->figure->GetHeight();
	}
	else {
		distanceY = textEdit->GetCriteriaHeight() - textEdit->figure->GetHeight();
	}
	FigureComposite *composite = static_cast<FigureComposite*>(textEdit->classDiagramForm->selection->GetAt(0));

	Finder finder;
	Long quadrant;
	Long i = 0;
	Long startX = composite->GetX();
	Long startY = composite->GetY();
	Long endX = composite->GetX() + composite->GetWidth();
	Long endY = composite->GetY() + composite->GetHeight();
	SmartPointer<Figure*> iterator(textEdit->classDiagramForm->diagram->CreateIterator());
	for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
		Long j = 0;
		FigureComposite *figureComposite = dynamic_cast<FigureComposite*>(iterator->Current());
		SmartPointer<Figure*> iterator_(figureComposite->CreateIterator());
		for (iterator_->First(); !iterator_->IsDone(); iterator_->Next()) {
			Figure *figure = iterator_->Current();
			if (dynamic_cast<Relation*>(iterator_->Current())) {
				Long relationEndX = figure->GetX() + figure->GetWidth();
				Long relationEndY = figure->GetY() + figure->GetHeight();
				if (startX <= relationEndX &&  relationEndX <= endX &&
					startY <= relationEndY &&  relationEndY <= endY) {
					quadrant = finder.FindQuadrant(relationEndX, relationEndY,
						startX, startY, endX, endY);
					if (quadrant == 3) {
						figure->EndPointMove(0, distanceY);
					}
				}
			}
		}
	}
	SmartPointer<Figure*> iterator__(composite->CreateIterator());
	for (iterator__->First(); !iterator__->IsDone(); iterator__->Next()) {
		if (iterator__->Current()->GetY() > textEdit->figure->GetY()) {
			iterator__->Current()->Move(0, distanceY);
		}
	}

	if (dynamic_cast<Class*>(composite)) {
		textEdit->figure->Modify(textEdit->figure->GetX(), textEdit->figure->GetY(), textEdit->figure->GetWidth(),
			textEdit->figure->GetHeight() + distanceY);
	}
	composite->Modify(composite->GetX(), composite->GetY(), composite->GetWidth(), composite->GetHeight() + distanceY);
}

void EditResizerProcess::ResizeEditWidthToLeft(TextEdit *textEdit, CDC *cdc) {
	RECT rt;
	textEdit->GetClientRect(&rt); //최대화 상태에서만 정상적인 rect를 출력. 최소화X
	

	
	int vertCurPos = textEdit->classDiagramForm->GetScrollPos(SB_VERT);
	int horzCurPos = textEdit->classDiagramForm->GetScrollPos(SB_HORZ);

	textEdit->SetWindowPos(&textEdit->wndTopMost,
		textEdit->figure->GetX() + GabX - (textEdit->text->MaxWidth(cdc) - rt.right) - CaretWidth - horzCurPos,
		textEdit->figure->GetY() + GabY - vertCurPos,
		rt.right + (textEdit->text->MaxWidth(cdc) - rt.right) + CaretWidth,
		rt.bottom, SWP_NOZORDER | SWP_NOREDRAW | SWP_NOCOPYBITS);
}

void EditResizerProcess::ResizeTemplateWidth(TextEdit *textEdit) {
	//RECT rt;
	//textEdit->GetWindowRect(&rt);
	//
	//textEdit->figure->Modify(rt.left - GabX,
	//	textEdit->figure->GetY(),
	//	rt.right - rt.left + GabX*2,
	//	textEdit->figure->GetHeight());
	RECT rt;
	textEdit->GetClientRect(&rt);

	textEdit->figure->Modify(textEdit->figure->GetX() - (rt.right + GabX*2 + CaretWidth - textEdit->figure->GetWidth()),
		textEdit->figure->GetY(),
		rt.right + GabX*2 + CaretWidth,
		textEdit->figure->GetHeight());
}

void EditResizerProcess::AffectedRelation(TextEdit *textEdit) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;

	Class *object = dynamic_cast<Class*>(textEdit->classDiagramForm->selection->GetAt(0));
	Long i = 0;
	Finder finder;
	while (i < object->GetLength()) {
		if (dynamic_cast<Relation*>(object->GetAt(i))) {
			Relation *relation = static_cast<Relation*>(object->GetAt(i));
			if (relation->GetX() >= textEdit->figure->GetX() - 10) {
				relation->Modify(textEdit->figure->GetX() - 10, relation->GetY(), relation->GetWidth() + relation->GetX() - textEdit->figure->GetX() + 10,
					relation->GetHeight());
				if (relation->GetLength() == 0) {
					CPoint startPoint{ relation->GetX(), relation->GetY() };
					CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
					cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
					cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
					cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
					cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
					cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
					relation->rollNamePoints->Modify(0, cPoint1);
					relation->rollNamePoints->Modify(1, cPoint2);
					relation->rollNamePoints->Modify(2, cPoint3);
					relation->rollNamePoints->Modify(3, cPoint4);
					relation->rollNamePoints->Modify(4, cPoint5);
				}
				else {
					CPoint startPoint{ relation->GetX(), relation->GetY() };
					CPoint endPoint{ relation->GetAt(0).x, relation->GetAt(0).y };
					cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
					cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
					relation->rollNamePoints->Modify(0, cPoint1);
					relation->rollNamePoints->Modify(3, cPoint4);

					CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
						relation->GetAt(relation->GetLength() - 1).y };
					CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
					cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
					cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
					relation->rollNamePoints->Modify(2, cPoint3);
					relation->rollNamePoints->Modify(4, cPoint5);

					if (relation->GetLength() % 2 == 0) {//짝수

						CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
							relation->GetAt((relation->GetLength() - 1) / 2).y };
						CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
							relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
						cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
						relation->rollNamePoints->Modify(1, cPoint2);

					}
					else {//홀수

						CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
							relation->GetAt((relation->GetLength() - 1) / 2).y };
						cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
						relation->rollNamePoints->Modify(1, cPoint2);

					}
				}
			}
		}
		i++;
	}//여기부터 끝점 이동/ 이거하고나서 템플릿 생성될때 그자리에 관계선 있을때/ 템플릿 이 있는자리에 관계선 그을때
}