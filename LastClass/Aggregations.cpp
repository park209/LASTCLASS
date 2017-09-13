#include "Aggregations.h"

Aggregations::Aggregations() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

Aggregations::Aggregations(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Aggregations::~Aggregations() {

}

Aggregations::Aggregations(const Aggregations& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
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