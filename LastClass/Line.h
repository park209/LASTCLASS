//Line.h
#ifndef _LINE_H
#define _LINE_H
#include "Figure.h"

typedef signed long int Long;

class Line : public Figure {
public:
	Line();
	Line(Long x, Long y, Long width, Long height);
	Line(const Line& source);
	virtual ~Line();

	void Accept(Visitor& visitor, CDC *cPaintDc);
	Line& operator = (const Line& source);
	Figure* Clone();
};

#endif // _LINE_H