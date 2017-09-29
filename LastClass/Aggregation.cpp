//Aggregation.cpp
//С§Че

#include "Aggregation.h"
#include "RollNameBox.h"

Aggregation::Aggregation(Long capacity):Relation(capacity) {
}

Aggregation::Aggregation(Long x, Long y, Long width, Long height): Relation(x,y,width,height) {
	this->rollNamePoints = new Array<CPoint>(5);
	this->rollNames = new Array<string>(5);
	CPoint startPoint{ x, y };
	CPoint endPoint{ x + width, y + height };

	RollNameBox *rollNameBox = RollNameBox::Instance();
	this->rollNamePoints->Modify(0, rollNameBox->GetFirstRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(1, rollNameBox->GetSecondRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(2, rollNameBox->GetThirdRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(3, rollNameBox->GetFourthRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(4, rollNameBox->GetFifthRollNamePoint(startPoint, endPoint));
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