//WritingVisitor.h

#ifndef _WRITINGVISITOR_H
#define _WRITINGVISITOR_H

#include "Visitor.h"

class WritingVisitor : public Visitor {
public:
	WritingVisitor();
	~WritingVisitor();

	void Visit(Line *line, CDC* cPaintDc);
	void Visit(Class *object, CDC* cPaintDc);
	void Visit(SingleByteCharacter *singleByteCharacter, CDC* cPaintDc);
	void Visit(DoubleByteCharacter *doubleByteCharacter, CDC* cPaintDc);
};

#endif // _WRITINGVISITOR_H