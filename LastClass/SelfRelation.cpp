//SelfRelation.cpp

#include "SelfRelation.h"

SelfRelation::SelfRelation() :Figure() {

}

SelfRelation::SelfRelation(Long x, Long y, Long width, Long height):Figure(x,y,width,height) {

}

SelfRelation::SelfRelation(const SelfRelation& source) : Figure(source) {

}

SelfRelation::~SelfRelation() {

}

SelfRelation& SelfRelation::operator=(const SelfRelation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}