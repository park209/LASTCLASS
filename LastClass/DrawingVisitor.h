//DrawingVisitor.h

#ifndef _DRAWINGVISITOR_H
#define _DRAWINGVISITOR_H

#include "Visitor.h"

typedef signed long  int Long;
class DrawingVisitor :public Visitor {
public:
	DrawingVisitor();
	~DrawingVisitor();

	void Visit(Class *object, CDC* cPaintDc);
	void Visit(Line *line, CDC* cPaintDc);
	void Visit(SingleByteCharacter *singleByteCharacter, CDC* cPaintDc);
	void Visit(DoubleByteCharacter *doubleByteCharacter, CDC* cPaintDc);
};

#endif // _DRAWINGVISITOR_H
