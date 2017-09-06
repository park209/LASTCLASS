//Visitor.h

#ifndef _VISITOR_H
#define _VISITOR_H

#include <afxwin.h>

class SingleByteCharacter;
class DoubleByteCharacter;
class Diagram;
class Class;
class Line;
class Relation;
class Visitor {
public:
	virtual ~Visitor();

	virtual void Visit(Class *object, CDC* cPaintDc) = 0;
	virtual void Visit(Line *line, CDC* cPaintDc) = 0;
	virtual void Visit(SingleByteCharacter *singleByteCharacter, CDC* cPaintDc) = 0;
	virtual void Visit(DoubleByteCharacter *doubleByteCharacter, CDC* cPaintDc) = 0;
	virtual void Visit(Relation *relation)=0; //0904Ãß°¡	CDC* cPaintDc) 
protected:
	Visitor();
};

#endif // _VISITOR_H
