//DrawingVisitor.cpp
#include"DrawingVisitor.h"
#include "Class.h"
DrawingVisitor::DrawingVisitor() {
}
void DrawingVisitor::VisitDiagram(Diagram *diagram, CDC* cPaintDc) {

}

void DrawingVisitor::VisitClass(Class *object, CDC* cPaintDc) {

	Long x = object->GetX();
	Long  y = object->GetY();;
	Long width = object->GetWidth();
	Long height = object->GetHeight();
	
	cPaintDc->Rectangle(x, y, x + width, y + height);
}
void DrawingVisitor::VisitLine(Line *line, CDC* cPaintDc) {
	Long x = line->GetX();
	Long  y = line->GetY();;
	Long width = line->GetWidth();
	// height = line->GetHeight();
	cPaintDc->MoveTo(x, y);
	cPaintDc->LineTo(x + width, y);
}

DrawingVisitor::~DrawingVisitor() {
}