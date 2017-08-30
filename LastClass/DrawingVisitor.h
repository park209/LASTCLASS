#pragma once
//DrawingVisitor.h
#ifndef _DRAWINGVISITOR_H
#define _DRAWINGVISITOR_H
#include "Visitor.h"
typedef signed long  int Long;
class DrawingVisitor :public Visitor {
public:
	DrawingVisitor();
	virtual ~DrawingVisitor();

	virtual void VisitDiagram(Diagram *diagram, CDC* cPaintDc);
	virtual void VisitClass(Class *object, CDC* cPaintDc);
	virtual void VisitLine(Line *line, CDC* cPaintDc);
};
#endif // !_DRAWINGVISITOR_H
