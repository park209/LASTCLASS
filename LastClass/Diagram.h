//Diagram.h

#ifndef _DIAGRAM_H
#define _DIAGRAM_H

#include "Class.h"

class Diagram : public FigureComposite {
public:
	Diagram(Long capacity = 256);
	Diagram(const Diagram& source);
	virtual ~Diagram();

	Diagram& operator = (const Diagram& source);
	Figure* operator [] (Long index);

	Long Add(Figure *figure);
	Long Add(Long x, Long y, Long width, Long height);
	Long Find(Long pointX, Long pointY);
	//void Find(Long startX, Long startY, Long width, Long height, Class* (*classes), Long count);//추가
	Long Remove(Long index);
	Class* GetAt(Long index);

	Figure* Clone() const;
	void PrintClass(SmartPointer<Figure*>& index);
	void Accept(Visitor& visitor, CDC *cPaintDc);

	Long GetCapacity() const;
	Long GetLength() const;
	Long GetCount() const;
public:
	Class* (*classes);//Class*갖고있는 변수 추가
	Long count;/////////
};
inline Long Diagram::GetCapacity() const {
	return this->capacity;
}
inline Long Diagram::GetLength() const {
	return this->length;
}
inline Long Diagram::GetCount() const {
	return this->count;
}

#endif // _DIAGRAM_H