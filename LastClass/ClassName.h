#ifndef _CLASSNAME_H
#define _CLASSNAME_H

#include "Figure.h"
#include "WritingVisitor.h"

typedef signed long int Long;

class ClassName : public Figure {

public:
	ClassName();
	ClassName(Long x, Long y, Long width, Long height, string content);
	ClassName(const ClassName& source);
	virtual ~ClassName();

	ClassName& operator = (const ClassName& source);

	void Accept(Visitor& visitor, CDC *cPaintDc);
	Figure* Clone() const;
};

#endif // _CLASSNAME_H
