#pragma once
#ifndef _AGGREGATIONS_H
#define _AGGREGATIONS_H


#include "Relation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
class Aggregations : public Relation {
public:
	Aggregations();
	Aggregations(Long x, Long y, Long width, Long height);
	Aggregations(const Aggregations& source);
	virtual ~Aggregations();

	Aggregations& operator = (const Aggregations&  source);
	void Accept(Visitor& visitor, CDC *cPaintDc);
	Figure* Clone() const;

};
#endif // !_AGGREGATIONS_H
