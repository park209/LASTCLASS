#include "Dependency.h"

Dependency::Dependency() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}


Dependency::Dependency(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Dependency::~Dependency() {

}

Dependency::Dependency(const Dependency& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}

Dependency& Dependency::operator=(const Dependency& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Dependency::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);//, cPaintDc);
}


Figure* Dependency::Clone() const {
	return new Dependency(*this);
}