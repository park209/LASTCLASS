#ifndef _ATTRIBUTE_H
#define _ATTRIBUTE_H

#include "Figure.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
class Attribute : public Figure {

public:
	Attribute();
	Attribute(Long x, Long y, Long width, Long height, string content);
	Attribute(const Attribute& source);
	virtual ~Attribute();

	Attribute& operator = (const Attribute& source);

	void Accept(Visitor& visitor, CDC *cPaintDc);
	Figure* Clone() const;
};

#endif // !_CLASSNAME_H