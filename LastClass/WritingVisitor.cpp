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
	
	cPaintDc->TextOut(singleByteCharacter->GetX(), singleByteCharacter->GetY(), singleByteCharacter->MakeCString());
}

void WritingVisitor::Visit(DoubleByteCharacter *doubleByteCharacter, CDC* cPaintDc) {
	cout << "	Double Visit doubleCharacter 적는다" << endl;

	cPaintDc->TextOut(doubleByteCharacter->GetX(), doubleByteCharacter->GetY(), doubleByteCharacter->MakeCString());
}

void WritingVisitor::Visit(Row* row, CDC* cPaintDc) {
	cout << "	Double Visit doubleCharacter 적는다" << endl;

	cPaintDc->TextOut(row->GetX(), row->GetY(), (CString)row->PrintRowString().c_str());
}
