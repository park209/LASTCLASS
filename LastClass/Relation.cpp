//Relation.cpp
#include "Relation.h"

Relation::Relation() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}
Relation::Relation(const Relation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}

Relation& Relation::operator=(const Relation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}
Relation::~Relation() {
}


