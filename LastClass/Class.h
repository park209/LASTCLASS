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
	Class(Long capacity = 4);  // ������ Line�� �ϰ�
	Class(Long x, Long y, Long width, Long height); // ���� �׸�(Ŭ�������̾�׷� ��ȣ)
	Class(const Class& source);
	virtual ~Class();

	Class& operator = (const Class& source);
	Figure* operator [] (Long index);

	Long Add(Long x, Long y, Long width, Long height);
	Long Add(Long x, Long y, Long width, Long height, Type type);	//0904�߰�
	Long Add(Figure *figure);
	Long Remove(Long index);

	Figure* GetAt(Long index);  


	Figure* Clone() const;
	void PrintLine(SmartPointer<Figure*>& index);
	void Accept(Visitor& visitor, CDC *cPaintDc);

	Long GetCapacity() const;
	Long GetLength() const;
};

inline Long Class::GetCapacity() const {
	return this->capacity;
}
inline Long Class::GetLength() const {
	return this->length;
}

#endif //_CLASS_H