#include "Composition.h"
#include "RollNameBox.h"

Composition::Composition(Long capacity):Relation(capacity){

}


Composition::Composition(Long x, Long y, Long width, Long height): Relation(x,y,width,height){
	CPoint startPoint{ x, y };
	CPoint endPoint{ x + width, y + height };

	RollNameBox *rollNameBox = RollNameBox::Instance();
	this->rollNamePoints->Modify(0, rollNameBox->GetFirstRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(1, rollNameBox->GetSecondRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(2, rollNameBox->GetThirdRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(3, rollNameBox->GetFourthRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(4, rollNameBox->GetFifthRollNamePoint(startPoint, endPoint));
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
