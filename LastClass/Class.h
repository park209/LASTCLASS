//Class.h

#ifndef _CLASS_H
#define _CLASS_H

#include "FigureComposite.h"
#include "Line.h"
#include "Iterator.h"
#include "SmartPointer.h"
#include "Relation.h"

class Class : public FigureComposite {
public:
	Class(Long capacity = 256);  // ������ Line�� �ϰ�
	Class(Long x, Long y, Long width, Long height); // ���� �׸�(Ŭ�������̾�׷� ��ȣ)
	Class(const Class& source);
	virtual ~Class();

	Class& operator = (const Class& source);
	Figure* operator [] (Long index);

	Long Add(Long x, Long y, Long width, Long height);
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




	Long Add(Figure *figure);
	Long Remove(Long index);

	Figure* GetAt(Long index);  


	Figure* Clone() const;
	void PrintLine(SmartPointer<Figure*>& index);
	void Accept(Visitor& visitor, CDC *cPaintDc);

	Long GetCapacity() const;
	Long GetLength() const;
	Long GetTempletePosition() const;
private:
	Long templetePosition;
};
inline Long Class::GetTempletePosition() const {
	return this->templetePosition;
}
inline Long Class::GetCapacity() const {
	return this->capacity;
}
inline Long Class::GetLength() const {
	return this->length;
}

#endif //_CLASS_H