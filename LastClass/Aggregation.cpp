//Aggregation.cpp
//С§Че

#include "Aggregation.h"

Aggregation::Aggregation() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

Aggregation::Aggregation(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Aggregation::~Aggregation() {

}

Aggregation::Aggregation(const Aggregation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}

Aggregation& Aggregation::operator=(const Aggregation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Aggregation::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this,cPaintDc);//, cPaintDc);
}

Figure* Aggregation::Clone() const {
	return new Aggregation(*this);
}