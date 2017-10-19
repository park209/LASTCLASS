//LeftSelfRelation.cpp

#include "RollNameBox.h"
#include "LeftSelfRelation.h"

LeftSelfRelation::LeftSelfRelation() :Figure() {
}

LeftSelfRelation::LeftSelfRelation(Long x, Long y, Long width, Long height) : Figure(x, y, width, height) {

	this->rollNamePoints = new Array<CPoint>(5);
	this->rollNames = new Array<string>(5);

	CPoint startPoint1And4{ x, y };
	CPoint endPoint1And4{ x , y - 40 };

	CPoint startPoint2{ x, y - 40 };
	CPoint endPoint2{ x - 80,  y - 40 };

	CPoint startPoint3And5{ x - 80, y - 40 };
	CPoint endPoint3And5{ x - 30,  y - 40 };

	RollNameBox *rollNameBox = RollNameBox::Instance();
	//this->rollNamePoints->Store(0, rollNameBox->GetLeftSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4));
	//this->rollNamePoints->Store(1, rollNameBox->GetLeftSelfRelationSecondRollNamePoint(startPoint2, endPoint2));
	//this->rollNamePoints->Store(2, rollNameBox->GetLeftSelfRelationThirdRollNamePoint(startPoint3And5, endPoint3And5));
	//this->rollNamePoints->Store(3, rollNameBox->GetLeftSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4));
	//this->rollNamePoints->Store(4, rollNameBox->GetLeftSelfRelationFifthRollNamePoint(startPoint3And5, endPoint3And5));
}

LeftSelfRelation::LeftSelfRelation(const LeftSelfRelation& source) : Figure(source) {
	//this->capacity = source.capacity;
	//this->length = source.length;
	this->rollNamePoints = source.rollNamePoints;
	this->rollNames = source.rollNames;
}

LeftSelfRelation::~LeftSelfRelation() {
}

LeftSelfRelation& LeftSelfRelation::operator=(const LeftSelfRelation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void LeftSelfRelation::ReplaceString(string rollNameText, Long rollNameBoxIndex) {
	this->rollNames->Modify(rollNameBoxIndex, rollNameText);
}

//void LeftSelfRelation::Accept(Visitor& visitor, CDC *cPaintDc) {
//	visitor.Visit(this, cPaintDc);
//}
