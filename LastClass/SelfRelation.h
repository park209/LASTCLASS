//SelfRelation.h

#ifndef _SELFRELATION_H
#define _SELFRELATION_H

#include "Figure.h"
#include "Array.h"
#include <afxwin.h>

typedef signed long int Long; 

class SelfRelation :public Figure {

public:
	SelfRelation();
	SelfRelation(Long x, Long y, Long width, Long height);
	SelfRelation(const SelfRelation& source);
	virtual ~SelfRelation() = 0;
	SelfRelation& operator =(const SelfRelation& source);

	Figure* Clone()const = 0;
public:
	Array<string>* rollNames;
	Array<CPoint>* rollNamePoints;
};

#endif // !_SELFRELATION_H

