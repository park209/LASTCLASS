#include "Generalization.h"
#include "RollNameBox.h"

Generalization::Generalization(Long capacity):Relation(capacity){
}


Generalization::Generalization(Long x, Long y, Long width, Long height) : Relation(x,y,width,height) {
	CPoint startPoint{ x, y };
	CPoint endPoint{ x + width, y + height };

	RollNameBox *rollNameBox = RollNameBox::Instance();
	this->rollNamePoints->Modify(0, rollNameBox->GetFirstRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(1, rollNameBox->GetSecondRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(2, rollNameBox->GetThirdRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(3, rollNameBox->GetFourthRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(4, rollNameBox->GetFifthRollNamePoint(startPoint, endPoint));
}

Generalization::~Generalization() {

}

Generalization::Generalization(const Generalization& source):Relation(source){
	
}

Generalization& Generalization::operator=(const Generalization& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Generalization::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);
}

Figure* Generalization::Clone() const {
	return new Generalization(*this);
}
