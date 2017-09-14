

//Visitor.h

#ifndef _VISITOR_H
#define _VISITOR_H

#include <afxwin.h>

class SingleByteCharacter;
class DoubleByteCharacter;
class Diagram;
class Class;
class Line;
class Row;
class Relation;
class Generalization;
class Realization;
class Dependency;
class Association;
class DirectedAssociation;
class Aggregation;
class Aggregations;
class Composition;
class Compositions;
class Template;
class MemoBox;
class MemoLine;
class ClassName;
class Method;
class Attribute;

class Visitor{
public:
	virtual ~Visitor();

	virtual void Visit(Class *object, CDC* cPaintDc) = 0;
	virtual void Visit(Line *line, CDC* cPaintDc) = 0;
	virtual void Visit(SingleByteCharacter *singleByteCharacter, CDC* cPaintDc) = 0;
	virtual void Visit(DoubleByteCharacter *doubleByteCharacter, CDC* cPaintDc) = 0;
	virtual void Visit(Row* row, CDC* cPaintDc) = 0;

	//, CDC* cPaintDc) = 0; //0904추가	CDC* cPaintDc)   0907관계선일반화관계로수정

	virtual void Visit(Generalization *generalization, CDC* cPaintDc) = 0;		//일반화

	virtual void Visit(Realization * realization, CDC* cPaintDc) = 0;		//실체화

	virtual void Visit(Dependency *dependency, CDC* cPaintDc) = 0;		//의존

	virtual void Visit(Association *association, CDC* cPaintDc) = 0;		//연관화 , CDC* cPaintDc

	virtual void Visit(DirectedAssociation *directedAssociation, CDC* cPaintDc) = 0;		//직접연관

	virtual void Visit(Aggregation *aggregation, CDC* cPaintDc) = 0;		//집합

	virtual void Visit(Aggregations *aggregations, CDC* cPaintDc) = 0;		//집합연관

	virtual void Visit(Composition *composition, CDC* cPaintDc) = 0;		//합성

	virtual void Visit(Compositions *compositions, CDC* cPaintDc) = 0;		//복합연관

	virtual void Visit(Template *object, CDC *cPaintDc) = 0;

	virtual void Visit(MemoBox* memobox, CDC *cPaintDc) = 0;// CDC  *cPaintDc

	virtual void Visit(MemoLine* memobox, CDC *cPaintDc) = 0;// CDC  *cPaintDc

	virtual void Visit(ClassName *className, CDC *cPaintDc) = 0;

	virtual void Visit(Method *method, CDC *cPaintDc) = 0;

	virtual void Visit(Attribute *attribute, CDC *cPaintDc) = 0;
protected:
	Visitor();
};

#endif // _VISITOR_H
