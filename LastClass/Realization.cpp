#include "Realization.h"

Realization::Realization() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}


Realization::Realization(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Realization::~Realization() {

}

Realization::Realization(const Realization& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}

Realization& Realization::operator=(const Realization& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Realization::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);//, cPaintDc);
}


Figure* Realization::Clone() const {
	return new Realization(*this);
}