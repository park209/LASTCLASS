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
	Long Remove(Long index);
	Class* GetAt(Long index);

	Figure* Clone() const;
	void PrintClass(SmartPointer<Figure*>& index);
	void Accept(Visitor& visitor, CDC *cPaintDc);

	Long GetCapacity() const;
	Long GetLength() const;
};

inline Long Diagram::GetCapacity() const {
	return this->capacity;
}
inline Long Diagram::GetLength() const {
	return this->length;
}

#endif // _DIAGRAM_H