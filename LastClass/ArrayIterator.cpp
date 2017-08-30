//ArrayIterator.cpp

#include "ArrayIterator.h"

ArrayIterator::ArrayIterator(const Array<Figure*>* array) {
	this->array = array;
	this->current = 0;
}

void ArrayIterator::First() {
	this->current = 0;
}

void ArrayIterator::Next() {
	this->current++;
}

bool ArrayIterator::IsDone() const {
	bool ret = true;
	if (this->current < this->array->GetLength() - 1) {
		ret = false;
	}
	return ret;
}

Figure* ArrayIterator::Current() const {
	return (const_cast<Array<Figure*>*>(this->array))->GetAt(this->current);
}