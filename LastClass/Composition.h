#pragma once
#ifndef _COMPOSITION_H
#define _COMPOSITION_H


#include "Relation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
class Composition : public Relation {
public:
	Composition();
	Composition(Long x, Long y, Long width, Long height);
	Composition(const Composition& source);
	virtual ~Composition();

	Composition& operator = (const Composition&  source);
	void Accept(Visitor& visitor, CDC *cPaintDc);
	Figure* Clone() const;

};
#endif // !_COMPOSITION_H
