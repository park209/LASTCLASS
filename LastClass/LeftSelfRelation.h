//LeftSelfRelation.h

#ifndef _LEFTSELFRELATION_H
#define _LEFTSELFRELATION_H

#include "Array.h"
#include <afxwin.h>
#include "Figure.h"
#include "WritingVisitor.h"

typedef signed long int Long;

class LeftSelfRelation :public Figure {

public:
	LeftSelfRelation();
	LeftSelfRelation(Long x, Long y, Long width, Long height);
	LeftSelfRelation(const LeftSelfRelation& source);
	virtual ~LeftSelfRelation() = 0;
	LeftSelfRelation& operator =(const LeftSelfRelation& source);

	void ReplaceString(string rollNameText, Long rollNameBoxIndex);
	void Accept(Visitor& visitor, CDC *cPaintDc);
	Figure* Clone()const = 0;
public:
	Array<string>* rollNames;
	Array<CPoint>* rollNamePoints;
};
#endif // _LEFTSELFRELATION_H

