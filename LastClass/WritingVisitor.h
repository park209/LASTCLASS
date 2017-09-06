//WritingVisitor.h

#ifndef _WRITINGVISITOR_H
#define _WRITINGVISITOR_H

#include "Visitor.h"

class SingleByteCharacter;
class DoubleByteCharacter;

class WritingVisitor : public Visitor {
public:
	WritingVisitor();
	~WritingVisitor();

	void Visit(Line *line, CDC* cPaintDc);
	void Visit(Class *object, CDC* cPaintDc);
	void Visit(SingleByteCharacter *singleByteCharacter, CDC* cPaintDc);
	void Visit(DoubleByteCharacter *doubleByteCharacter, CDC* cPaintDc);
	void Visit(Relation *relation);
};

#endif // _WRITINGVISITOR_H