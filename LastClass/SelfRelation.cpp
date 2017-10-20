//SelfRelation.cpp

#include "RollNameBox.h"
#include "SelfRelation.h"

SelfRelation::SelfRelation() :Figure() {
	this->leftRigtFlag = 0;
}

SelfRelation::SelfRelation(Long x, Long y, Long width, Long height) : Figure(x, y, width, height) {
	this->leftRigtFlag = 0;
	this->rollNamePoints = new Array<CPoint>(5);
	this->rollNames = new Array<string>(5);

	CPoint startPoint1And4{ x, y };
	CPoint endPoint1And4{ x , y - 40 };

	CPoint startPoint2{ x, y - 40 };
	CPoint endPoint2{ x + 80,  y - 40 };

	CPoint startPoint3And5{ x + 80, y + 40 };
	CPoint endPoint3And5{ x + 30,  y + 40 };

	RollNameBox *rollNameBox = RollNameBox::Instance();
	this->rollNamePoints->Store(0, rollNameBox->GetSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4));
	this->rollNamePoints->Store(1, rollNameBox->GetSelfRelationSecondRollNamePoint(startPoint2, endPoint2));
	this->rollNamePoints->Store(2, rollNameBox->GetSelfRelationThirdRollNamePoint(startPoint3And5, endPoint3And5));
	this->rollNamePoints->Store(3, rollNameBox->GetSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4));
	this->rollNamePoints->Store(4, rollNameBox->GetSelfRelationFifthRollNamePoint(startPoint3And5, endPoint3And5));
}

SelfRelation::SelfRelation(const SelfRelation& source) : Figure(source) {
	this->leftRigtFlag = source.leftRigtFlag;
	//this->capacity = source.capacity;
	//this->length = source.length;
	this->rollNamePoints = source.rollNamePoints;
	this->rollNames = source.rollNames;
}

SelfRelation::~SelfRelation() {
}

SelfRelation& SelfRelation::operator=(const SelfRelation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->leftRigtFlag = source.leftRigtFlag;
	return *this;
}

void SelfRelation::ReplaceString(string rollNameText, Long rollNameBoxIndex) {
	this->rollNames->Modify(rollNameBoxIndex, rollNameText);
}

void SelfRelation::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);
}
