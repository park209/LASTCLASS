#pragma once

//Association.h
// ����ȭ

#ifndef _ASSOCIATION_H
#define _ASSOCIATION_H

#include "Relation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;

class Association : public Relation {
public:
	Association();
	Association(Long x, Long y, Long width, Long height);
	Association(const Association& source);
	virtual ~Association();

	Association& operator = (const Association&  source);
	void Accept(Visitor& visitor, CDC *cPaintDc); //, CDC *cPaintDc
	Figure* Clone() const;

};
#endif // _ASSOCIATION_H