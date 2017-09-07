#pragma once
#ifndef _GENERALIZATION_H
#define _GENERALIZATION_H


#include "Relation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
class Generalization : public Relation{
public:
	Generalization();
	Generalization(Long x, Long y, Long width, Long height);
	Generalization(const Generalization& source);
	virtual ~Generalization();

	Generalization& operator = (const Generalization&  source);
	void Accept(Visitor& visitor, CDC *cPaintDc);
	Figure* Clone() const;

};
#endif // !_GENERALIZATION_H
