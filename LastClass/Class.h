

//Class.h

#ifndef _CLASS_H
#define _CLASS_H

#include "FigureComposite.h"
#include "DrawingVisitor.h"

class Class : public FigureComposite {
public:
	Class(Long capacity = 256);  // ������ Line�� �ϰ�
	Class(Long x, Long y, Long width, Long height); // ���� �׸�(Ŭ�������̾�׷� ��ȣ)
	Class(const Class& source);
	virtual ~Class();

	Class& operator = (const Class& source);
	Figure* operator [] (Long index);


	Long Add(Long x, Long y, Long width, Long height);
	Figure* Move(Long distanceX, Long distanceY);


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




	virtual Long Add(Figure *figure);
	virtual Long Remove(Long index);

	virtual Figure* GetAt(Long index);


	virtual Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *cPaintDc);

	Long GetTempletePosition() const;

private:
	Long templetePosition;
};
inline Long Class::GetTempletePosition() const {
	return this->templetePosition;
}

#endif //_CLASS_H