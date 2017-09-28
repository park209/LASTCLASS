#include "Composition.h"
#include  "RollNameBox.h"
Composition::Composition(Long capacity):Relation(capacity){

}


Composition::Composition(Long x, Long y, Long width, Long height): Relation(x,y,width,height){
	CPoint startPoint{ x, y };
	CPoint endPoint{ x + width, y + height };
	RollNameBox *boxPoint = RollNameBox::Instance();
	this->rollNamePoints->Modify(0, boxPoint->GetFirstRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(1, boxPoint->GetSecondRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(2, boxPoint->GetThirdRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(3, boxPoint->GetFourthRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(4, boxPoint->GetFifthRollNamePoint(startPoint, endPoint));
}

Composition::~Composition() {

}

Composition::Composition(const Composition& source):Relation(source){

}

Composition& Composition::operator=(const Composition& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Composition::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);
}


Figure* Composition::Clone() const {
	return new Composition(*this);
}
