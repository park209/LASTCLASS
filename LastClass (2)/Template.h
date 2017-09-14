

#ifndef _TEMPLATE_H
#define _TEMPLATE_H

#include "Figure.h"
#include "DrawingVisitor.h"

typedef signed long int Long;

class Template : public Figure {
public:
	Template();
	Template(Long x, Long  y, Long width, Long height);
	Template(const Template& source);
	virtual ~Template();

	Template& operator=(const Template& source);
	void Accept(Visitor& visitor, CDC *cPaintDc);
	Figure* Clone() const;
};







#endif // !_TEMPLATE_H
