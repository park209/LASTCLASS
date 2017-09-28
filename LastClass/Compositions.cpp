#include "Compositions.h"
#include "RollNameBox.h"

Compositions::Compositions(Long capacity):Relation(capacity){

}


Compositions::Compositions(Long x, Long y, Long width, Long height): Relation(x,y,width,height){
	CPoint startPoint{ x, y };
	CPoint endPoint{ x + width, y + height };

	RollNameBox *rollNameBox = RollNameBox::Instance();
	this->rollNamePoints->Modify(0, rollNameBox->GetFirstRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(1, rollNameBox->GetSecondRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(2, rollNameBox->GetThirdRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(3, rollNameBox->GetFourthRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(4, rollNameBox->GetFifthRollNamePoint(startPoint, endPoint));
}

Compositions::~Compositions() {

}

Compositions::Compositions(const Compositions& source):Relation(source){

}

Compositions& Compositions::operator=(const Compositions& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Compositions::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);//, cPaintDc);
}


Figure* Compositions::Clone() const {
	return new Compositions(*this);
}
