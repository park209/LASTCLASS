//MovingVisitor.cpp

#include"MovingVisitor.h"
#include "Diagram.h"
#include "Class.h"
#include "MemoBox.h"
#include "Selection.h"
#include "Template.h"
#include "Line.h"
#include "Generalization.h"
#include "Realization.h"
#include "Dependency.h"
#include "Association.h"
#include "DirectedAssociation.h"
#include "Aggregation.h"
#include "Aggregations.h"
#include "Composition.h"
#include "Compositions.h"
#include "MemoLine.h"
#include <iostream>
#include "Finder.h"

using namespace std;

MovingVisitor::MovingVisitor() {
}
MovingVisitor::~MovingVisitor() {
}
void MovingVisitor::Visit(Diagram *diagram, Selection *selection, Long distanceX, Long distanceY) {
	Long length = selection->GetLength();
	Long i = 0;
	Long j;
	Long k;
	Long l = 0;
	Figure *figure;
	Finder finder;
	Figure *(*figures) = new Figure*[32];
	Long length2=0;
	while (i < length) {
		figure = selection->GetAt(i);


		if (dynamic_cast<FigureComposite*>(figure)) { //클래스나 메모면
			FigureComposite *figureComposite = static_cast<FigureComposite*>(figure);
			finder.FindRelationEndPoints(diagram, figureComposite, figures, &length2);
			k = 0;
			while (k < length2) {
				figures[k]->EndPointMove(distanceX, distanceY);
				k++;
			}
			figure->Move(distanceX, distanceY); // 해당 클래스나 메모 이동
			 // 형변환
			j = 0;
			while (j < figureComposite->GetLength()) { // 형변환 한게 관리하면 배열 렝스까지
				figure = figureComposite->GetAt(j);
				figure->Move(distanceX, distanceY);
				j++;
			}
		}
		i++;
	}
	delete figures;
}
void MovingVisitor::Visit(Class *object, CDC* cPaintDc) {
}
void MovingVisitor::Visit(MemoBox *memoBox, CDC *cPaintDc) {
}
void MovingVisitor::Visit(Selection *selection, CDC *cPaintDc) {
}
void MovingVisitor::Visit(Template *object, CDC *cPaintDc) {
}
void MovingVisitor::Visit(ClassName* className, CDC* cPaintDc) {
}
void MovingVisitor::Visit(Attribute* attribute, CDC* cPaintDc) {;
}
void MovingVisitor::Visit(Method* method, CDC* cPaintDc) {
}
void MovingVisitor::Visit(Reception* reception, CDC* cPaintDc) {
}
void MovingVisitor::Visit(Line *line, CDC* cPaintDc) {
}
void MovingVisitor::Visit(Generalization *generalization, CDC* cPaintDc) {
}
void MovingVisitor::Visit(Realization *realization, CDC* cPaintDc) {
}
void MovingVisitor::Visit(Dependency *dependency, CDC* cPaintDc) {
}
void MovingVisitor::Visit(Association *association, CDC* cPaintDc) {
}
void MovingVisitor::Visit(DirectedAssociation *directedAssociation, CDC* cPaintDc) {
}
void MovingVisitor::Visit(Aggregation *aggregation, CDC* cPaintDc) {
}
void MovingVisitor::Visit(Aggregations *aggregations, CDC* cPaintDc) {
}
void MovingVisitor::Visit(Composition *composition, CDC* cPaintDc) {
}
void MovingVisitor::Visit(Compositions *compositions, CDC* cPaintDc) {
}
void MovingVisitor::Visit(MemoLine *memoLine, CDC *cPaintDc) {
}
void MovingVisitor::Visit(SelfGeneralization *selfGeneralization, CDC *cPaintDc) {
}
void MovingVisitor::Visit(SelfDependency *selfDependency, CDC *cPaintDc) {
}
void MovingVisitor::Visit(SelfAggregation *selfAggregation, CDC *cPaintDc) {
}
void MovingVisitor::Visit(SelfAssociation *selfAssociation, CDC *cPaintDc) {
}
void MovingVisitor::Visit(SelfAggregations *selfAggregations, CDC *cPaintDc) {
}
void MovingVisitor::Visit(SelfDirectedAssociation *selfDirectedAssociation, CDC *cPaintDc) {
}
void MovingVisitor::Visit(SelfComposition *selfComposition, CDC *cPaintDc) {
}
void MovingVisitor::Visit(SelfCompositions *selfCompositions, CDC *cPaintDc) {
}
void MovingVisitor::Visit(Text* text, CDC* cPaintDc) {
}