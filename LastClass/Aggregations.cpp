#include "Aggregations.h"
#include "RollNameBox.h"
Aggregations::Aggregations(Long capacity):Relation(capacity){

}

Aggregations::Aggregations(Long x, Long y, Long width, Long height): Relation(x,y,width,height){
	CPoint startPoint{ x, y };
	CPoint endPoint{ x + width, y + height };
	RollNameBox *boxPoint = RollNameBox::Instance();
	this->rollNamePoints->Modify(0, boxPoint->GetFirstRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(1, boxPoint->GetSecondRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(2, boxPoint->GetThirdRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(3, boxPoint->GetFourthRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(4, boxPoint->GetFifthRollNamePoint(startPoint, endPoint));
}

Aggregations::~Aggregations() {

}

Aggregations::Aggregations(const Aggregations& source): Relation(source){
}

Aggregations& Aggregations::operator=(const Aggregations& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Aggregations::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);//, cPaintDc);
}


Figure* Aggregations::Clone() const {
	return new Aggregations(*this);
}
//
//#include <iostream>
//using namespace std;
//
//int main(int argc, char *argv[]) {
//	Aggregations aggregations(20, 30, 40, 50);
//
//	Aggregations aggregations1(100, 100, 200, 300);
//
//	DrawingVisitor drawingVisitor;
//
//	Aggregations aggregations2(aggregations1);
//
//	aggregations.Accept(drawingVisitor);
//
//	aggregations1.Accept(drawingVisitor);
//
//	aggregations2.Accept(drawingVisitor);
//
//	aggregations1 = aggregations;
//
//	aggregations1.Accept(drawingVisitor);
//
//	Figure *figure = aggregations2.Clone();
//
//	static_cast<Aggregations*>(figure)->Accept(drawingVisitor);
//
//	return 0;
//}