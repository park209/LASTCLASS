//Class.h

#ifndef _CLASS_H
#define _CLASS_H

#include "FigureComposite.h"
#include "Line.h"
#include "Iterator.h"
#include "SmartPointer.h"

class Class : public FigureComposite {
public:
	Class(Long capacity = 4);  // 관리는 Line을 하고
	Class(Long x, Long y, Long width, Long height); // 본인 그림(클래스다이어그램 기호)
	Class(const Class& source);
	virtual ~Class();

	Class& operator = (const Class& source);
	Figure* operator [] (Long index);

	Long Add(Long x, Long y, Long width, Long height);
	Long Add(Figure *figure);
	Long Remove(Long index);
	Line* GetAt(Long index);

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