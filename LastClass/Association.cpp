//Association.cpp
// ¿¬°üÈ­

#include "Association.h"

Association::Association() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

Association::Association(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Association::~Association() {

}

Association::Association(const Association& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}

Association& Association::operator=(const Association& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Association::Accept(Visitor& visitor, CDC *cPaintDc) { //, CDC *cPaintDc
	visitor.Visit(this, cPaintDc);
}

Figure* Association::Clone() const {
	return new Association(*this);
}