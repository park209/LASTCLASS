//ArrayIterator.h
#ifndef _ARRAYITERATOR_H
#define _ARRAYITERATOR_H
#include "Iterator.h"
#include "Array.h"

typedef signed long int Long;
class Figure;
class ArrayIterator : public Iterator<Figure*> {
public:
	ArrayIterator(const Array<Figure*>* array);
	virtual void First();
	virtual void Next();
	virtual bool IsDone() const;
	virtual Figure* Current() const;
private:
	const Array <Figure*>* array;
	Long current;
};

#endif // !_ARRAYITERATOR_H