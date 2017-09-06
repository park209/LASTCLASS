//WritingVIsitor.cpp

#include "WritingVisitor.h"
#include "SingleByteCharacter.h"

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
	cout << "	Single Visit singleCharacter ���´�" << endl;
	
	char character;
	character = singleByteCharacter->GetCharacter();
	CString cs(character);
	cPaintDc->TextOut(singleByteCharacter->GetX(), singleByteCharacter->GetY(), cs);
}

void WritingVisitor::Visit(DoubleByteCharacter *doubleByteCharacter, CDC* cPaintDc) {
	cout << "	Double Visit doubleCharacter ���´�" << endl;

}

void WritingVisitor::Visit(Relation *relation) {
}