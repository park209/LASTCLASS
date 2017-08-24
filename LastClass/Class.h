//Class.h
#ifndef _CLASS_H
#define _CLASS_H

#include "Array.h"
#include "Line.h"
#include <string>
using namespace std;

typedef signed long int Long;
class Class {
public:
	Class(Long capacity = 3);
	Class(Long x, Long y, Long width, Long height, Long capacity = 3);
	Class(Long x, Long y, Long width, Long height, string name, Long capacity = 3);
	Class(const Class& source);

	Long Add(Long startX, Long startY, Long endX, Long endY);
	Line& GetAt(Long index);

	Line& operator [] (Long index);
	Line* operator + (Long index);
	Class& operator = (const Class& source);

	~Class();

	Long GetCapacity() const;
	Long GetLength() const;
	Long GetX() const;
	Long GetY() const;
	Long GetWidth() const;
	Long GetHeight() const;
	string& GetName() const;
private:
	Array<Line> lines;
	Long capacity;
	Long length;
	Long x;
	Long y;
	Long width;
	Long height;
	string name;
};
inline Long Class::GetCapacity() const {
	return this->capacity;
}
inline Long Class::GetLength() const {
	return this->length;
}
inline Long Class::GetX()const {
	return this->x;
}
inline Long Class::GetY()const {
	return this->y;
}
inline Long Class::GetWidth()const {
	return this->width;
}
inline Long Class::GetHeight()const {
	return this->height;
}
inline string& Class::GetName() const {
	return const_cast<string&>(this->name);
}

#endif // !_CLASS_H

