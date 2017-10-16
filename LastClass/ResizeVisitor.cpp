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

ResizeVisitor::ResizeVisitor(Long previousZoomRate, Long nextZoomRate) {
	this->previousZoomRate = previousZoomRate;
	this->nextZoomRate = nextZoomRate;
}
ResizeVisitor::~ResizeVisitor() {
}

void ResizeVisitor::Visit(Diagram *diagram, Selection *selection, Long distanceX, Long distanceY) {
}

void ResizeVisitor::Visit(Class *object, CDC* cPaintDc) {
	object->SetX(object->GetX() * this->nextZoomRate / this->previousZoomRate);
	object->SetY(object->GetY() * this->nextZoomRate / this->previousZoomRate);
	object->SetWidth(object->GetWidth() * this->nextZoomRate / this->previousZoomRate);
	object->SetHeight(object->GetHeight() *this->nextZoomRate / this->previousZoomRate);
	//object->SetMinimumWidth(object->GetMinimumWidth() * zoomRate / 100);
	//object->SetMinimumWidth(object->GetMinimumHeight() * zoomRate / 100);
}

void ResizeVisitor::Visit(Text* text, CDC* cPaintDc) {
}

void  ResizeVisitor::Visit(SelfRelation *selfRelation, CDC *cPaintDc) {
	selfRelation->SetX(selfRelation->GetX() * this->nextZoomRate / this->previousZoomRate);
	selfRelation->SetY(selfRelation->GetY() * this->nextZoomRate / this->previousZoomRate);
	selfRelation->SetWidth(selfRelation->GetWidth() * this->nextZoomRate / this->previousZoomRate);
	selfRelation->SetHeight(selfRelation->GetHeight() * this->nextZoomRate / this->previousZoomRate);
}

void  ResizeVisitor::Visit(Relation *relation, CDC *pDC) {
	relation->SetX(relation->GetX() * this->nextZoomRate / this->previousZoomRate);
	relation->SetY(relation->GetY() * this->nextZoomRate / this->previousZoomRate);
	relation->SetWidth(relation->GetWidth() * this->nextZoomRate / this->previousZoomRate);
	relation->SetHeight(relation->GetHeight() * this->nextZoomRate / this->previousZoomRate);
	
	Long i = 0;
	CPoint tempPoint;
	while (i < relation->GetLength()) {
		tempPoint = relation->GetAt(i);
		tempPoint.x = tempPoint.x * this->nextZoomRate / this->previousZoomRate;
		tempPoint.y = tempPoint.y * this->nextZoomRate / this->previousZoomRate;
		relation->Correct(i, tempPoint);
		i++;
	}
}

void ResizeVisitor::Visit(MemoBox *memoBox, CDC *cPaintDc) {
	memoBox->SetX(memoBox->GetX() * this->nextZoomRate / this->previousZoomRate);
	memoBox->SetY(memoBox->GetY() * this->nextZoomRate / this->previousZoomRate);
	memoBox->SetWidth(memoBox->GetWidth() * this->nextZoomRate / this->previousZoomRate);
	memoBox->SetHeight(memoBox->GetHeight() * this->nextZoomRate / this->previousZoomRate);
}

void ResizeVisitor::Visit(Selection *selection, CDC *cPaintDc) {
	selection->SetX(selection->GetX() * this->nextZoomRate / this->previousZoomRate);
	selection->SetY(selection->GetY() * this->nextZoomRate / this->previousZoomRate);
	selection->SetWidth(selection->GetWidth() * this->nextZoomRate / this->previousZoomRate);
	selection->SetHeight(selection->GetHeight() * this->nextZoomRate / this->previousZoomRate);
}

void ResizeVisitor::Visit(Template *object, CDC *cPaintDc) {
	object->SetX(object->GetX() * this->nextZoomRate / this->previousZoomRate);
	object->SetY(object->GetY() * this->nextZoomRate / this->previousZoomRate);
	object->SetWidth(object->GetWidth() * this->nextZoomRate / this->previousZoomRate);
	object->SetHeight(object->GetHeight() * this->nextZoomRate / this->previousZoomRate);
}

void ResizeVisitor::Visit(ClassName* className, CDC* cPaintDc) {

	className->SetX(className->GetX() * this->nextZoomRate / this->previousZoomRate);
	className->SetY(className->GetY() * this->nextZoomRate / this->previousZoomRate);
	className->SetWidth(className->GetWidth() * this->nextZoomRate / this->previousZoomRate);
	className->SetHeight(className->GetHeight() * this->nextZoomRate / this->previousZoomRate);
}

void ResizeVisitor::Visit(Attribute* attribute, CDC* cPaintDc) {
	attribute->SetX(attribute->GetX() * this->nextZoomRate / this->previousZoomRate);
	attribute->SetY(attribute->GetY() * this->nextZoomRate / this->previousZoomRate);
	attribute->SetWidth(attribute->GetWidth() * this->nextZoomRate / this->previousZoomRate);
	attribute->SetHeight(attribute->GetHeight() * this->nextZoomRate / this->previousZoomRate);
}
void ResizeVisitor::Visit(Method* method, CDC* cPaintDc) {
	method->SetX(method->GetX() * this->nextZoomRate / this->previousZoomRate);
	method->SetY(method->GetY() * this->nextZoomRate / this->previousZoomRate);
	method->SetWidth(method->GetWidth() * this->nextZoomRate / this->previousZoomRate);
	method->SetHeight(method->GetHeight() * this->nextZoomRate / this->previousZoomRate);
}
void ResizeVisitor::Visit(Reception* reception, CDC* cPaintDc) {
	reception->SetX(reception->GetX() * this->nextZoomRate / this->previousZoomRate);
	reception->SetY(reception->GetY() * this->nextZoomRate / this->previousZoomRate);
	reception->SetWidth(reception->GetWidth() * this->nextZoomRate / this->previousZoomRate);
	reception->SetHeight(reception->GetHeight() * this->nextZoomRate / this->previousZoomRate);
}

void ResizeVisitor::Visit(Line *line, CDC* cPaintDc) {
	line->SetX(line->GetX() * this->nextZoomRate / this->previousZoomRate);
	line->SetY(line->GetY() * this->nextZoomRate / this->previousZoomRate);
	line->SetWidth(line->GetWidth() * this->nextZoomRate / this->previousZoomRate);
	line->SetHeight(line->GetHeight() * this->nextZoomRate / this->previousZoomRate);
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

//리사이즈 텍스트
void ResizeVisitor::Visit(Text *text, Long zoomRate) {

}