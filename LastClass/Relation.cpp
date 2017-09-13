//Relation.cpp
#include "Relation.h"

Relation::Relation():Figure() {
}
Relation::Relation(const Relation& source) :Figure(source) {

}
Relation::Relation(Long x, Long y, Long width, Long height) :Figure(x,y,width,height){

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


