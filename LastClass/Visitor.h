#pragma once
//Visitor.h
#ifndef _VISITOR_H
#define _VISITOR_H
#include <afxwin.h>
class Diagram;
class Class;
class Line;

class Visitor {
public:
	virtual ~Visitor();
	virtual void VisitDiagram(Diagram *diagram, CDC* cPaintDc)=0;
	virtual void VisitClass(Class *object, CDC* cPaintDc)=0;
	virtual void VisitLine(Line *line, CDC* cPaintDc)=0;
	
protected:
	Visitor();
};

#endif // !_VISITOR_H
