//Method.h

#ifndef _METHOD_H
#define _METHOD_H

#include "Figure.h"
#include "DrawingVisitor.h"

typedef signed long int Long;

class Method : public Figure {

public:
	Method();
	Method(Long x, Long y, Long width, Long height, string content);
	Method(const Method& source);
	virtual ~Method();

	Method& operator = (const Method& source);

	//void Accept(Visitor& visitor, CDC *cPaintDc);
	Figure* Clone() const;
};

#endif // _METHOD_H