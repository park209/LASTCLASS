#include "Generalization.h"

Generalization::Generalization() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}


Generalization::Generalization(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Generalization::~Generalization() {

}

Generalization::Generalization(const Generalization& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}

Generalization& Generalization::operator=(const Generalization& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Generalization::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);//, cPaintDc);
}

Figure* Generalization::Clone() const {
	return new Generalization(*this);
}

