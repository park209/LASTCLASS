//Relation.cpp
#include "Relation.h"

Relation::Relation(Type type) {
	this->type = type;
}
Relation::Relation(Long x, Long y, Long width, Long height, Type type) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->type = type;
}
Relation::Relation(const Relation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->type = source.type;
}
Relation::~Relation() {

}
Relation& Relation::operator=(const Relation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->type = source.type;
	return *this;
}

void Relation::Accept(Visitor& visitor) {
	visitor.Visit(this);
}

Figure* Relation::Clone() const {
	return new Relation(*this);
}

