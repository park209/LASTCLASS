//DirectedAssociation.cpp
// 직접연관

#include "DirectedAssociation.h"

DirectedAssociation::DirectedAssociation() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

DirectedAssociation::DirectedAssociation(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

DirectedAssociation::~DirectedAssociation() {

}

DirectedAssociation::DirectedAssociation(const DirectedAssociation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}

DirectedAssociation& DirectedAssociation::operator=(const DirectedAssociation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void DirectedAssociation::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);//, cPaintDc);
}

Figure* DirectedAssociation::Clone() const {
	return new DirectedAssociation(*this);
}