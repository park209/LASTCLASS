
//Class.h

#ifndef _CLASS_H
#define _CLASS_H

#include "FigureComposite.h"
#include "DrawingVisitor.h"

class Class : public FigureComposite {
public:
	Class(Long capacity = 64);  // 관리는 Line을 하고
	Class(Long x, Long y, Long width, Long height); // 본인 그림(클래스다이어그램 기호)
	Class(const Class& source);
	virtual ~Class();

	Class& operator = (const Class& source);
	Figure* operator [] (Long index);


	Long Add(Long x, Long y, Long width, Long height);
	Figure* Move(Long distanceX, Long distanceY);
	void Initialize();

	Long AddGeneralization(Long x, Long y, Long width, Long height);
	Long AddRealization(Long x, Long y, Long width, Long height);
	Long AddDependency(Long x, Long y, Long width, Long height);
	Long AddAssociation(Long x, Long y, Long width, Long height);
	Long AddDirectedAssociation(Long x, Long y, Long width, Long height);
	Long AddAggregation(Long x, Long y, Long width, Long height);
	Long AddAggregations(Long x, Long y, Long width, Long height);
	Long AddComposition(Long x, Long y, Long width, Long height);
	Long AddCompositions(Long x, Long y, Long width, Long height);
	Long AddTemplate(Long x, Long y, Long width, Long height);

	Long RemoveTemplate();
	Long RemoveReception();
	Long AddReception(Diagram *diagram);


	virtual Long Add(Figure *figure);
	virtual Long Remove(Long index);

	virtual Figure* GetAt(Long index);


	virtual Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *cPaintDc);

	Long GetReceptionPosition() const;
	Long GetTempletePosition() const;

private:
	Long templetePosition;
	Long receptionPosition;
	Long attributePosition;
	Long methodPosition;
};
inline Long Class::GetTempletePosition() const {
	return this->templetePosition;
}
inline Long Class::GetReceptionPosition()const {
	return this->receptionPosition;
}

#endif //_CLASS_H