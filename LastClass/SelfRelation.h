//SelfRelation.h
#ifndef _SELFRELATION_H
#define _SELFRELATION_H

#include "Figure.h"
typedef signed long int Long; 

class SelfRelation :public Figure {

public:
	SelfRelation();
	SelfRelation(Long x, Long y, Long width, Long height);
	SelfRelation(const SelfRelation& source);
	virtual ~SelfRelation() = 0;
	SelfRelation& operator =(const SelfRelation& source);

	Figure* Clone()const = 0;

};
#endif // !_SELFRELATION_H

