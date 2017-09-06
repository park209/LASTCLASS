//DrawingVisitor.cpp

#include"DrawingVisitor.h"
#include "Class.h"
#include <iostream>
using namespace std;

DrawingVisitor::DrawingVisitor() {
}

void DrawingVisitor::Visit(Class *object, CDC* cPaintDc) {

	Long x = object->GetX();
	Long  y = object->GetY();;
	Long width = object->GetWidth();
	Long height = object->GetHeight();

	cout << "   Class �� �׸���" << endl;
	
	cPaintDc->Rectangle(x, y, x + width, y + height);
}
void DrawingVisitor::Visit(Line *line, CDC* cPaintDc) {
	Long x = line->GetX();
	Long  y = line->GetY();;
	Long width = line->GetWidth();

	cout << "   Line �� �׸���" << endl;
	
	cPaintDc->MoveTo(x, y);
	cPaintDc->LineTo(x + width, y);
}

void DrawingVisitor::Visit(SingleByteCharacter *singleByteCharacter, CDC* cPaintDc) {
}

void DrawingVisitor::Visit(DoubleByteCharacter *doubleByteCharacter, CDC* cPaintDc) {
}

void DrawingVisitor::Visit(Relation *relation) {
	cout << relation->GetX() << " " << relation->GetY() << " " << relation->GetWidth() << " " << relation->GetHeight() << " "
		<< relation->GetType() << endl;
}

DrawingVisitor::~DrawingVisitor() {
}