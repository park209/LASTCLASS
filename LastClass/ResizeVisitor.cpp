//ResizeVisitor.cpp

#include "ResizeVisitor.h"
#include "Diagram.h"

#include "Class.h"
#include "MemoBox.h"
#include "Relation.h"
#include "Line.h"
#include "SelfRelation.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "Reception.h"
#include "Template.h"
#include "Selection.h"
#include "MemoLine.h"
#include "RollNameBox.h"

ResizeVisitor::ResizeVisitor(Long previousZoomRate, Long nextZoomRate) {
	this->previousZoomRate = previousZoomRate;
	this->nextZoomRate = nextZoomRate;
}
ResizeVisitor::~ResizeVisitor() {
}

void ResizeVisitor::Visit(Diagram *diagram, Selection *selection, Long distanceX, Long distanceY) {
}

void ResizeVisitor::Visit(Class *object, CDC* cPaintDc) {
	object->SetX(object->GetPointToReal(object->GetX(), this->nextZoomRate, this->previousZoomRate));
	object->SetY(object->GetPointToReal(object->GetY(), this->nextZoomRate, this->previousZoomRate));
	object->SetWidth(object->GetPointToReal(object->GetWidth(), this->nextZoomRate, this->previousZoomRate));
	object->SetHeight(object->GetPointToReal(object->GetHeight(), this->nextZoomRate, this->previousZoomRate));
	//object->SetMinimumWidth(object->GetMinimumWidth() * zoomRate / 100);
	//object->SetMinimumWidth(object->GetMinimumHeight() * zoomRate / 100);
	static_cast<Figure*>(object)->SetMinimumWidth(object->GetPointToReal(object->GetMinimumWidth(), this->nextZoomRate, this->previousZoomRate));
	object->SetMinimumHeight(object->GetPointToReal(object->GetMinimumHeight(), this->nextZoomRate, this->previousZoomRate));
}

void ResizeVisitor::Visit(Text* text, CDC* cPaintDc) {
}

void  ResizeVisitor::Visit(SelfRelation *selfRelation, CDC *cPaintDc) {
	selfRelation->SetX(selfRelation->GetX() * this->nextZoomRate / this->previousZoomRate);
	selfRelation->SetY(selfRelation->GetY() * this->nextZoomRate / this->previousZoomRate);
	selfRelation->SetWidth(selfRelation->GetWidth() * this->nextZoomRate / this->previousZoomRate);
	selfRelation->SetHeight(selfRelation->GetHeight() * this->nextZoomRate / this->previousZoomRate);

	Long x = selfRelation->GetX();
	Long y = selfRelation->GetY();

	CPoint startPoint1And4{ x, y };
	CPoint endPoint1And4{ x , y - 40 * this->nextZoomRate / 100 };

	CPoint startPoint2{ x, y - 40 * this->nextZoomRate / 100 };
	CPoint endPoint2{ x + 80 * this->nextZoomRate / 100,  y - 40 * this->nextZoomRate / 100 };

	CPoint startPoint3And5{ x + 80 * this->nextZoomRate / 100, y + 40 * this->nextZoomRate / 100 };
	CPoint endPoint3And5{ x + 30 * this->nextZoomRate / 100,  y + 40 * this->nextZoomRate / 100 };

	RollNameBox *rollNameBox = RollNameBox::Instance();
	selfRelation->rollNamePoints->Store(0, rollNameBox->GetSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4));
	selfRelation->rollNamePoints->Store(1, rollNameBox->GetSelfRelationSecondRollNamePoint(startPoint2, endPoint2));
	selfRelation->rollNamePoints->Store(2, rollNameBox->GetSelfRelationThirdRollNamePoint(startPoint3And5, endPoint3And5));
	selfRelation->rollNamePoints->Store(3, rollNameBox->GetSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4));
	selfRelation->rollNamePoints->Store(4, rollNameBox->GetSelfRelationFifthRollNamePoint(startPoint3And5, endPoint3And5));
}

void  ResizeVisitor::Visit(Relation *relation, CDC *pDC) {
	Long relationX = relation->GetX() * this->nextZoomRate / this->previousZoomRate;
	Long relationY = relation->GetY() * this->nextZoomRate / this->previousZoomRate;
	relation->Modify(relationX, relationY,
		((relation->GetX() + relation->GetWidth()) * this->nextZoomRate / this->previousZoomRate) - relationX,
		((relation->GetY() + relation->GetHeight()) * this->nextZoomRate / this->previousZoomRate) - relationY);

	Long i = 0;
	CPoint tempPoint;
	while (i < relation->GetLength()) {
		tempPoint = relation->GetAt(i);
		tempPoint.x = tempPoint.x * this->nextZoomRate / this->previousZoomRate;
		tempPoint.y = tempPoint.y * this->nextZoomRate / this->previousZoomRate;
		relation->Correct(i, tempPoint);
		i++;
	}

	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	
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

void ResizeVisitor::Visit(MemoBox *memoBox, CDC *cPaintDc) {
	memoBox->SetX(memoBox->GetX() * this->nextZoomRate / this->previousZoomRate);
	memoBox->SetY(memoBox->GetY() * this->nextZoomRate / this->previousZoomRate);
	memoBox->SetWidth(memoBox->GetWidth() * this->nextZoomRate / this->previousZoomRate);
	memoBox->SetHeight(memoBox->GetHeight() * this->nextZoomRate / this->previousZoomRate);
	memoBox->SetMinimumWidth(memoBox->GetMinimumWidth() * this->nextZoomRate / this->previousZoomRate);
	memoBox->SetMinimumHeight(memoBox->GetMinimumHeight() * this->nextZoomRate / this->previousZoomRate);
}

void ResizeVisitor::Visit(Selection *selection, CDC *cPaintDc) {
	selection->SetX(selection->GetX() * this->nextZoomRate / this->previousZoomRate);
	selection->SetY(selection->GetY() * this->nextZoomRate / this->previousZoomRate);
	selection->SetWidth(selection->GetWidth() * this->nextZoomRate / this->previousZoomRate);
	selection->SetHeight(selection->GetHeight() * this->nextZoomRate / this->previousZoomRate);
}

void ResizeVisitor::Visit(Template *object, CDC *cPaintDc) {
	object->SetX(object->GetPointToReal(object->GetX(), this->nextZoomRate, this->previousZoomRate));
	object->SetY(object->GetPointToReal(object->GetY(), this->nextZoomRate, this->previousZoomRate));
	object->SetWidth(object->GetPointToReal(object->GetWidth(), this->nextZoomRate, this->previousZoomRate));
	object->SetHeight(object->GetPointToReal(object->GetHeight(), this->nextZoomRate, this->previousZoomRate));
	object->SetMinimumWidth(object->GetPointToReal(object->GetMinimumWidth(), this->nextZoomRate, this->previousZoomRate));
	object->SetMinimumHeight(object->GetPointToReal(object->GetMinimumHeight(), this->nextZoomRate, this->previousZoomRate));
}

void ResizeVisitor::Visit(ClassName* className, CDC* cPaintDc) {
	className->SetX(className->GetPointToReal(className->GetX(), this->nextZoomRate, this->previousZoomRate));
	className->SetY(className->GetPointToReal(className->GetY(), this->nextZoomRate, this->previousZoomRate));
	className->SetWidth(className->GetPointToReal(className->GetWidth(), this->nextZoomRate, this->previousZoomRate));
	className->SetHeight(className->GetPointToReal(className->GetHeight(), this->nextZoomRate, this->previousZoomRate));
	className->SetMinimumWidth(className->GetPointToReal(className->GetMinimumWidth(), this->nextZoomRate, this->previousZoomRate));
	className->SetMinimumHeight(className->GetPointToReal(className->GetMinimumHeight(), this->nextZoomRate, this->previousZoomRate));
}

void ResizeVisitor::Visit(Attribute* attribute, CDC* cPaintDc) {
	attribute->SetX(attribute->GetPointToReal(attribute->GetX(), this->nextZoomRate, this->previousZoomRate));
	attribute->SetY(attribute->GetPointToReal(attribute->GetY(), this->nextZoomRate, this->previousZoomRate));
	attribute->SetWidth(attribute->GetPointToReal(attribute->GetWidth(), this->nextZoomRate, this->previousZoomRate));
	attribute->SetHeight(attribute->GetPointToReal(attribute->GetHeight(), this->nextZoomRate, this->previousZoomRate));
	attribute->SetMinimumWidth(attribute->GetPointToReal(attribute->GetMinimumWidth(), this->nextZoomRate, this->previousZoomRate));
	attribute->SetMinimumHeight(attribute->GetPointToReal(attribute->GetMinimumHeight(), this->nextZoomRate, this->previousZoomRate));
}
void ResizeVisitor::Visit(Method* method, CDC* cPaintDc) {
	method->SetX(method->GetPointToReal(method->GetX(), this->nextZoomRate, this->previousZoomRate));
	method->SetY(method->GetPointToReal(method->GetY(), this->nextZoomRate, this->previousZoomRate));
	method->SetWidth(method->GetPointToReal(method->GetWidth(), this->nextZoomRate, this->previousZoomRate));
	method->SetHeight(method->GetPointToReal(method->GetHeight(), this->nextZoomRate, this->previousZoomRate));
	method->SetMinimumWidth(method->GetPointToReal(method->GetMinimumWidth(), this->nextZoomRate, this->previousZoomRate));
	method->SetMinimumHeight(method->GetPointToReal(method->GetMinimumHeight(), this->nextZoomRate, this->previousZoomRate));
}
void ResizeVisitor::Visit(Reception* reception, CDC* cPaintDc) {
	reception->SetX(reception->GetPointToReal(reception->GetX(), this->nextZoomRate, this->previousZoomRate));
	reception->SetY(reception->GetPointToReal(reception->GetY(), this->nextZoomRate, this->previousZoomRate));
	reception->SetWidth(reception->GetPointToReal(reception->GetWidth(), this->nextZoomRate, this->previousZoomRate));
	reception->SetHeight(reception->GetPointToReal(reception->GetHeight(), this->nextZoomRate, this->previousZoomRate));
	reception->SetMinimumWidth(reception->GetPointToReal(reception->GetMinimumWidth(), this->nextZoomRate, this->previousZoomRate));
	reception->SetMinimumHeight(reception->GetPointToReal(reception->GetMinimumHeight(), this->nextZoomRate, this->previousZoomRate));
}

void ResizeVisitor::Visit(Line *line, CDC* cPaintDc) {
	line->SetX(line->GetPointToReal(line->GetX(), this->nextZoomRate, this->previousZoomRate));
	line->SetY(line->GetPointToReal(line->GetY(), this->nextZoomRate, this->previousZoomRate));
	line->SetWidth(line->GetPointToReal(line->GetWidth(), this->nextZoomRate, this->previousZoomRate));
	line->SetHeight(line->GetPointToReal(line->GetHeight(), this->nextZoomRate, this->previousZoomRate));
}

void ResizeVisitor::Visit(Generalization *generalization, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Realization *realization, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Dependency *dependency, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Association *association, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(DirectedAssociation *directedAssociation, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Aggregation *aggregation, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Aggregations *aggregations, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Composition *composition, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Compositions *compositions, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(MemoLine *memoLine, CDC *cPaintDc) {
	memoLine->SetX(memoLine->GetX() * this->nextZoomRate / this->previousZoomRate);
	memoLine->SetY(memoLine->GetY() * this->nextZoomRate / this->previousZoomRate);
	memoLine->SetWidth(memoLine->GetWidth() * this->nextZoomRate / this->previousZoomRate);
	memoLine->SetHeight(memoLine->GetHeight() * this->nextZoomRate / this->previousZoomRate);
}
void ResizeVisitor::Visit(SelfGeneralization *selfGeneralization, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(SelfDependency *selfDependency, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(SelfAggregation *selfAggregation, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(SelfAssociation *selfAssociation, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(SelfAggregations *selfAggregations, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(SelfDirectedAssociation *selfDirectedAssociation, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(SelfComposition *selfComposition, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(SelfCompositions *selfCompositions, CDC *cPaintDc) {
}



void ResizeVisitor::Visit(Diagram *diagram, Long zoomRate) {
}

void ResizeVisitor::Visit(Class *object, Long zoomRate) {
	object->SetX(object->GetX() * zoomRate / 100);
	object->SetY(object->GetY() * zoomRate / 100);
	object->SetWidth(object->GetWidth() * zoomRate / 100);
	object->SetHeight(object->GetHeight() * zoomRate / 100);
	//object->SetMinimumWidth(object->GetMinimumWidth() * zoomRate / 100);
	//object->SetMinimumWidth(object->GetMinimumHeight() * zoomRate / 100);
}

void ResizeVisitor::Visit(MemoBox *memoBox, Long zoomRate) {
	memoBox->SetX(memoBox->GetX() * zoomRate / 100);
	memoBox->SetY(memoBox->GetY() * zoomRate / 100);
	memoBox->SetWidth(memoBox->GetWidth() * zoomRate / 100);
	memoBox->SetHeight(memoBox->GetHeight() * zoomRate / 100);
}

void ResizeVisitor::Visit(Relation *relation, Long zoomRate) {
	relation->SetX(relation->GetX() * zoomRate / 100);
	relation->SetY(relation->GetY() * zoomRate / 100);
	relation->SetWidth(relation->GetWidth() * zoomRate / 100);
	relation->SetHeight(relation->GetHeight() * zoomRate / 100);
}

void ResizeVisitor::Visit(Line *line, Long zoomRate) {
	line->SetX(line->GetX() * zoomRate / 100);
	line->SetY(line->GetY() * zoomRate / 100);
	line->SetWidth(line->GetWidth() * zoomRate / 100);
	line->SetHeight(line->GetHeight() * zoomRate / 100);
}

void ResizeVisitor::Visit(SelfRelation *selfRelation, Long zoomRate) {
	selfRelation->SetX(selfRelation->GetX() * zoomRate / 100);
	selfRelation->SetY(selfRelation->GetY() * zoomRate / 100);
	selfRelation->SetWidth(selfRelation->GetWidth() * zoomRate / 100);
	selfRelation->SetHeight(selfRelation->GetHeight() * zoomRate / 100);
}

void ResizeVisitor::Visit(ClassName *className, Long zoomRate) {
	className->SetX(className->GetX() * zoomRate / 100);
	className->SetY(className->GetY() * zoomRate / 100);
	className->SetWidth(className->GetWidth() * zoomRate / 100);
	className->SetHeight(className->GetHeight() * zoomRate / 100);
}

void ResizeVisitor::Visit(Attribute *attribute, Long zoomRate) {
	attribute->SetX(attribute->GetX() * zoomRate / 100);
	attribute->SetY(attribute->GetY() * zoomRate / 100);
	attribute->SetWidth(attribute->GetWidth() * zoomRate / 100);
	attribute->SetHeight(attribute->GetHeight() * zoomRate / 100);
}
void ResizeVisitor::Visit(Method *method, Long zoomRate) {
	method->SetX(method->GetX() * zoomRate / 100);
	method->SetY(method->GetY() * zoomRate / 100);
	method->SetWidth(method->GetWidth() * zoomRate / 100);
	method->SetHeight(method->GetHeight() * zoomRate / 100);
}
void ResizeVisitor::Visit(Reception *reception, Long zoomRate) {
	reception->SetX(reception->GetX() * zoomRate / 100);
	reception->SetY(reception->GetY() * zoomRate / 100);
	reception->SetWidth(reception->GetWidth() * zoomRate / 100);
	reception->SetHeight(reception->GetHeight() * zoomRate / 100);
}
void ResizeVisitor::Visit(Template *object, Long zoomRate) {
	object->SetX(object->GetX() * zoomRate / 100);
	object->SetY(object->GetY() * zoomRate / 100);
	object->SetWidth(object->GetWidth() * zoomRate / 100);
	object->SetHeight(object->GetHeight() * zoomRate / 100);
}

void ResizeVisitor::Visit(Class *object, Long distanceX, Long distanceY) {}
void ResizeVisitor::Visit(MemoBox *memoBox, Long distanceX, Long distanceY) {}

//리사이즈 텍스트
void ResizeVisitor::Visit(Text *text, Long zoomRate) {

}