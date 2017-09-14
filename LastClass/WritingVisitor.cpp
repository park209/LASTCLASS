//WritingVIsitor.cpp

#include "WritingVisitor.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Row.h"

WritingVisitor::WritingVisitor() {
}

WritingVisitor::~WritingVisitor() {
}

void WritingVisitor::Visit(Class *object, CDC* cPaintDc) {
}

void WritingVisitor::Visit(Line *line, CDC* cPaintDc) {
}

#include <iostream>
using namespace std;

void WritingVisitor::Visit(SingleByteCharacter *singleByteCharacter, CDC* cPaintDc) {
	cout << "	Single Visit singleCharacter 적는다" << endl;
	
	char character;
	character = singleByteCharacter->GetCharacter();
	CString cs(character);
	cPaintDc->TextOut(singleByteCharacter->GetX(), singleByteCharacter->GetY(), cs);
}

void WritingVisitor::Visit(DoubleByteCharacter *doubleByteCharacter, CDC* cPaintDc) {
	cout << "	Double Visit doubleCharacter 적는다" << endl;

}

void WritingVisitor::Visit(Row* row, CDC* cPaintDc) {
	//cout << "   Double Visit doubleCharacter 적는다" << endl;

	cPaintDc->TextOut(row->GetX(), row->GetY(), (CString)row->PrintRowString().c_str());
}

void WritingVisitor::Visit(Generalization *generalization, CDC* cPaintDc){
}

void WritingVisitor::Visit(Realization *realization, CDC* cPaintDc) {
}

void WritingVisitor::Visit(Dependency *dependency, CDC* cPaintDc) {
}

void WritingVisitor::Visit(Association *association, CDC* cPaintDc) { //, CDC* cPaintDc
}

void WritingVisitor::Visit(DirectedAssociation *directedAssociation, CDC* cPaintDc) {
}

void WritingVisitor::Visit(Aggregation *aggregation, CDC* cPaintDc) {
}

void WritingVisitor::Visit(Aggregations *aggregations, CDC* cPaintDc) {
}

void WritingVisitor::Visit(Composition *composition, CDC* cPaintDc) {
}

void WritingVisitor::Visit(Compositions *compositions, CDC* cPaintDc) {
}
void WritingVisitor::Visit(Template *object, CDC *cPaintDc) {
}
void WritingVisitor::Visit(MemoBox *memoBox, CDC *cPaintDc) { // CDC  *cPaintDc
}
void WritingVisitor::Visit(MemoLine *memoLine, CDC *cPaintDc) {
}
void WritingVisitor::Visit(ClassName *className, CDC *cPaintDc) {

}

void WritingVisitor::Visit(Method *method, CDC *cPaintDc) {

}
void WritingVisitor::Visit(Attribute *attribute, CDC *cPaintDc) {

}

void WritingVisitor::Visit(Selection *selection, CDC *cPaintDc) {
}