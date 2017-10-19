//LeftSelfAggregation.h

#ifndef _LEFTSELFAGGREGATION_H
#define _LEFTSELFAGGREGATION_H

#include "LeftSelfRelation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
class LeftSelfAggregation :public LeftSelfRelation {
public:
	LeftSelfAggregation();
	LeftSelfAggregation(Long x, Long y, Long width, Long height);
	LeftSelfAggregation(const LeftSelfAggregation& source);
	LeftSelfAggregation& operator = (const LeftSelfAggregation& source);

	virtual ~LeftSelfAggregation();
	Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *pDC);

};
#endif // _LEFTSELFAGGREGATION_H

