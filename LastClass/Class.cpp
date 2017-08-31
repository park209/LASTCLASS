//Class.cpp

#include "Class.h"

Class::Class(Long capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

Class::Class(Long x, Long y, Long width, Long height) {
	this->capacity = 8;
	this->length = 0;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Class::Class(const Class& source) {
	this->figures = source.figures;
	Long i = 0;
	while (i < source.length) {
		this->figures.Modify(i, (const_cast<Class&>(source)).figures[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}

Class::~Class() {
}

Class& Class::operator = (const Class& source) {
	this->figures = source.figures;
	Long i = 0;
	while (i < source.length) {
		this->figures.Modify(i, (const_cast<Class&>(source)).figures[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;

	return *this;
}

Long Class::Add(Figure *figure) {
	Long index;
	if (this->length < this->capacity) {
		index = this->figures.Store(this->length, figure);
	}
	else {
		index = this->figures.AppendFromRear(figure);
		this->capacity++;
	}
	this->length++;

	return index;
}

Long Class::Add(Long x, Long y, Long width, Long height) {
	Long index;
	Line object(x, y, width, height);

	if (this->length < this->capacity) {
		index = this->figures.Store(this->length, object.Clone());
	}
	else {
		index = this->figures.AppendFromRear(object.Clone());
		this->capacity++;
	}
	this->length++;

	return index;
}

Long Class::Remove(Long index) {

	return this->figures.Delete(index);
}


Figure* Class::GetAt(Long index) { 
	return this->figures.GetAt(index);
}

Figure* Class::Clone() const{
	return new Class(*this);
}

void Class::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.VisitClass(this, cPaintDc);
	SmartPointer<Figure*> smartPointer(this->CreateIterator());
	while (!smartPointer->IsDone()) {
		smartPointer->Current()->Accept(visitor, cPaintDc);
		smartPointer->Next();
	}
}
