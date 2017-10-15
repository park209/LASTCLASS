//ResizeVisitor.cpp

#include "ResizeVisitor.h"
#include "Diagram.h"
ResizeVisitor::ResizeVisitor() {
}
ResizeVisitor::~ResizeVisitor() {
}
void ResizeVisitor::Visit(Diagram *diagram, Selection *selection, Long distanceX, Long distanceY) {
}
void ResizeVisitor::Visit(Class *object, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Class *object, Long distanceX, Long distanceY) {
}
void ResizeVisitor::Visit(Text* text, CDC* cPaintDc) {
}

void  ResizeVisitor::Visit(SelfRelation *selfRelation, CDC *cPaintDc) {
}

void  ResizeVisitor::Visit(Relation *relation, CDC *pDC) {
}
void ResizeVisitor::Visit(MemoBox *memoBox, Long distanceX, Long distanceY) {
}
void ResizeVisitor::Visit(MemoBox *memoBox, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(Selection *selection, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(Template *object, CDC *cPaintDc) {
}

void ResizeVisitor::Visit(ClassName* className, CDC* cPaintDc) {
}

void ResizeVisitor::Visit(Attribute* attribute, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Method* method, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Reception* reception, CDC* cPaintDc) {
}

void ResizeVisitor::Visit(Line *line, CDC* cPaintDc) {
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
}
void ResizeVisitor::Visit(Relation *relation, Long zoomRate) {
}
void ResizeVisitor::Visit(MemoBox *memoBox, Long zoomRate) {
}
void ResizeVisitor::Visit(Line *line, Long zoomRate) {
}
void ResizeVisitor::Visit(SelfRelation *selfRelation, Long zoomRate) {
}
void ResizeVisitor::Visit(ClassName *className, Long zoomRate) {
}
void ResizeVisitor::Visit(Attribute *attribute, Long zoomRate) {
}
void ResizeVisitor::Visit(Method *method, Long zoomRate) {
}
void ResizeVisitor::Visit(Reception *reception, Long zoomRate) {
}
void ResizeVisitor::Visit(Template *object, Long zoomRate) {
}

//리사이즈 텍스트
void ResizeVisitor::Visit(Text *text, Long zoomRate) {
}