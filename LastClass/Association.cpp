//Association.cpp
// ¿¬°üÈ­

#include "Association.h"
#include "RollNameBox.h"

Association::Association(Long capacity) :Relation(capacity){
}

Association::Association(Long x, Long y, Long width, Long height):Relation(x,y,width,height) {
	CPoint startPoint{ x, y };
	CPoint endPoint{ x + width, y + height };

	RollNameBox *rollNameBox = RollNameBox::Instance();
	this->rollNamePoints->Modify(0, rollNameBox->GetFirstRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(1, rollNameBox->GetSecondRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(2, rollNameBox->GetThirdRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(3, rollNameBox->GetFourthRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(4, rollNameBox->GetFifthRollNamePoint(startPoint, endPoint));
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