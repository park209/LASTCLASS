//Diagram.h
#ifndef DIAGRAM_H
#define DIAGRAM_H

#include "Class.h"
#include "Array.h"

class Diagram {
public:
	Diagram(Long capacity = 256);
	Diagram(const Diagram& source);
	Long Add(Long x, Long y, Long width, Long height);
	Class GetAt(Long index);

	Diagram& operator = (const Diagram& source);
	Class& operator [](Long index);

	Long GetCapacity()const;
	Long GetLength()const;

	~Diagram();
private:
	Array<Class> classes;
	Long capacity;
	Long length;
};
inline Long Diagram::GetCapacity() const {
	return this->capacity;
}
inline Long Diagram::GetLength() const {
	return this->length;
}
#endif // _DIAGRAM_H
