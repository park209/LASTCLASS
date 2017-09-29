#include "Dependency.h"
#include "RollNameBox.h"

Dependency::Dependency(Long capacity):Relation( capacity){

}


Dependency::Dependency(Long x, Long y, Long width, Long height) : Relation(x,y,width,height){
	CPoint startPoint{ x, y };
	CPoint endPoint{ x + width, y + height };

	RollNameBox *rollNameBox = RollNameBox::Instance();
	this->rollNamePoints->Modify(0, rollNameBox->GetFirstRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(1, rollNameBox->GetSecondRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(2, rollNameBox->GetThirdRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(3, rollNameBox->GetFourthRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(4, rollNameBox->GetFifthRollNamePoint(startPoint, endPoint));
}

Dependency::~Dependency() {

}

Dependency::Dependency(const Dependency& source) :Relation(source){

}

Dependency& Dependency::operator=(const Dependency& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Dependency::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);
}


Figure* Dependency::Clone() const {
	return new Dependency(*this);
}