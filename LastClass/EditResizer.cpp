//EditResizer.cpp

#include "RollNameBox.h"
#include "EditResizer.h"
#include "EditResizerProcess.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Figure.h"
#include "FigureComposite.h"
#include "Diagram.h"
#include "Class.h"
#include "Finder.h"
#include "Selection.h"
#include "MemoBox.h"
#include "Relation.h"
#include "ClassName.h"
#include "Template.h"
#include "SelfRelation.h"

EditResizer::EditResizer() {

}
EditResizer::EditResizer(const EditResizer& source) {

}
EditResizer::~EditResizer() {

}

void EditResizer::ResizeEdit(TextEdit *textEdit, CDC *cdc) {
	if (!dynamic_cast<Relation*>(textEdit->figure) && !dynamic_cast<SelfRelation*>(textEdit->figure)) {
		EditResizerProcess resizer;
		RECT rt;
		textEdit->GetClientRect(&rt);
		Long gabY_ = GabY * 2;
		if (dynamic_cast<MemoBox*>(textEdit->figure) || dynamic_cast<ClassName*>(textEdit->figure)) {
			gabY_ += MemoGab;
		}

		if (textEdit->text->MaxWidth(cdc) + GabX * 2 + CaretWidth > textEdit->GetCriteriaWidth()) {         //글너비가 클래스를 넘어가는데
			if (textEdit->GetRowHeight()*textEdit->text->GetLength() + gabY_ > textEdit->GetCriteriaHeight()) {
				resizer.ResizeEditAll(textEdit, cdc);                                          //글높이가 클래스를 넘어가면 둘다O
			}
			else if (!dynamic_cast<Template*>(textEdit->figure)) {                                 //글높이가 클래스를 안넘어가면 너비만
				resizer.ResizeEditWidth(textEdit, cdc);
			}
			else {                                                                     //템플릿이면 템플릿너비만
				resizer.ResizeEditWidthToLeft(textEdit, cdc);

			}
		}                                                                           //글너비가 클래스를 안넘어가는데
		else if (textEdit->GetRowHeight()*textEdit->text->GetLength() + gabY_ > textEdit->GetCriteriaHeight()) {
			resizer.ResizeEditHeight(textEdit, cdc);
		}
		else {
			//글높이가 클래스를 넘어가면 둘다X
			resizer.RewindEdit(textEdit, cdc);
		}
	}
}

void EditResizer::ResizeClass(TextEdit *textEdit, CDC *cdc) {
	EditResizerProcess resizer;
	RECT rt;
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	textEdit->GetClientRect(&rt);
	if (!dynamic_cast<Relation*>(textEdit->figure) && !dynamic_cast<Template*>(textEdit->figure) && !dynamic_cast<SelfRelation*>(textEdit->figure)) {
		ClassDiagramForm *classDiagramForm = (ClassDiagramForm*)textEdit->GetParent();
		Long gabY_ = GabY * 2;

		if (dynamic_cast<Class*>(classDiagramForm->selection->GetAt(0))) {
			textEdit->figure->SetMinimumWidth(textEdit->text->MaxWidth(cdc) + GabX * 2);
			static_cast<Class*>(classDiagramForm->selection->GetAt(0))->SetMinimumWidth();
		}
		else {
			gabY_ += MemoGab;
			if (textEdit->text->MaxWidth(cdc) + GabX * 2 > 120) {
				textEdit->figure->SetMinimumWidth(textEdit->text->MaxWidth(cdc) + GabX * 2);
			}
		}
		textEdit->figure->SetMinimumHeight(textEdit->GetRowHeight()*textEdit->text->GetLength() + gabY_);
		resizer.ResizeClassWidth(textEdit);
		resizer.ResizeClassHeight(textEdit);
	}
	else if (dynamic_cast<Template*>(textEdit->figure)) {
		if (rt.right + GabX * 2 + CaretWidth > textEdit->GetCriteriaWidth()) {
			resizer.ResizeTemplateWidth(textEdit);
			ClassDiagramForm *classDiagramForm = (ClassDiagramForm*)textEdit->GetParent();
			Class *object = dynamic_cast<Class*>(classDiagramForm->selection->GetAt(0));
			Long i = 0;
			Finder finder;
			Long Quadrant;
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
			}
			//여기부터 끝점 이동/ 이거하고나서 템플릿 생성될때 그자리에 관계선 있을때/ 템플릿 이 있는자리에 관계선 그을때
		}
	}
}