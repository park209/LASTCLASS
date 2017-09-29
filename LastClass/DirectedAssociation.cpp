//DirectedAssociation.cpp
// 직접연관

#include "DirectedAssociation.h"
#include "RollNameBox.h"

DirectedAssociation::DirectedAssociation(Long capacity) :Relation( capacity){

}

DirectedAssociation::DirectedAssociation(Long x, Long y, Long width, Long height): Relation(x,y,width,height){
	CPoint startPoint{ x, y };
	CPoint endPoint{ x + width, y + height };

	RollNameBox *rollNameBox = RollNameBox::Instance();
	this->rollNamePoints->Modify(0, rollNameBox->GetFirstRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(1, rollNameBox->GetSecondRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(2, rollNameBox->GetThirdRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(3, rollNameBox->GetFourthRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(4, rollNameBox->GetFifthRollNamePoint(startPoint, endPoint));
}

DirectedAssociation::~DirectedAssociation() {

}

DirectedAssociation::DirectedAssociation(const DirectedAssociation& source):Relation(source){

}

DirectedAssociation& DirectedAssociation::operator=(const DirectedAssociation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void DirectedAssociation::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);
}

Figure* DirectedAssociation::Clone() const {
	return new DirectedAssociation(*this);
}