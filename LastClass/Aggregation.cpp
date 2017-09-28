//Aggregation.cpp
//С§Че

#include "Aggregation.h"

Aggregation::Aggregation(Long capacity):Relation(capacity) {
}

Aggregation::Aggregation(Long x, Long y, Long width, Long height): Relation(x,y,width,height){
	CPoint startPoint{ x, y };
	CPoint endPoint{ x + width, y + height };

	//this->rollNamePoints[0] = 

}

Aggregation::~Aggregation() {

}

Aggregation::Aggregation(const Aggregation& source):Relation(source){
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