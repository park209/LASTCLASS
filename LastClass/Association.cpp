//Association.cpp
// ����ȭ

#include "Association.h"

Association::Association(Long capacity) :Relation(capacity){
}

Association::Association(Long x, Long y, Long width, Long height):Relation(x,y,width,height) {
}

Association::~Association() {

}

Association::Association(const Association& source) :Relation(source){

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