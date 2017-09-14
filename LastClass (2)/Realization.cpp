#include "Realization.h"

Realization::Realization() :Relation(){

}


Realization::Realization(Long x, Long y, Long width, Long height): Relation(x,y,width,height){
	
}

Realization::~Realization() {

}

Realization::Realization(const Realization& source):Relation(source){

}

Realization& Realization::operator=(const Realization& source){
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