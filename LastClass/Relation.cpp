//Relation.cpp
#include "Relation.h"

Relation::Relation(Long capacity):Figure(){
	this->points;
	this->capacity = capacity;
	this->length = 0;
}


Relation::Relation(const Relation& source) :Figure(source), points(source.points) {
	Long i = 0;
	while (i < source.length) {
		this->points.Modify(i, const_cast<Relation&>(source).points[i]);
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;

}
Relation::Relation(Long x, Long y, Long width, Long height) :Figure(x,y,width,height), points() {
	this->capacity = capacity;
	this->length = 0;
}
Relation& Relation::operator=(const Relation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	Long i = 0;
	while (i < source.length) {
		this->points.Modify(i, const_cast<Relation&>(source).points[i]);
		i++;
	}
	return *this;
}

Relation::~Relation() {
}

Long Relation::Move(Long index, CPoint cPoint) {
		return this->points.Modify(index, cPoint);
}
CPoint Relation::GetAt(Long index) {
	return this->points.GetAt(index);
}
Long Relation::Add(CPoint cPoint) {
	Long index;
	if (this->length < this->capacity) {
		index = this->points.Store(this->length, cPoint);
	}
	else {
		index = this->points.AppendFromRear(cPoint);
		this->capacity++;
	}
	this->length++;

	return index;
}
Long Relation::Remove(Long index) {
	return this->points.Delete(index);
}
Long Relation::Find(CPoint cPoint) {
	Long i = 0;
	while (i < this->length && cPoint != this->GetAt(i)) {
		i++;
	}
	if (i >= this->length) {
		i = -1;
	}

	return i;
}
