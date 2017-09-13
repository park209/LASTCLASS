#include "Compositions.h"

Compositions::Compositions() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}


Compositions::Compositions(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Compositions::~Compositions() {

}

Compositions::Compositions(const Compositions& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
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
//
//#include <iostream>
//using namespace std;
//
//int main(int argc, char *argv[]) {
//	Compositions compositions(20,30,40,50);
//
//	Compositions compositions1(100, 100, 200, 300);
//
//	DrawingVisitor drawingvisitor;
//
//	Compositions compositions2(compositions1);
//
//	compositions.Accept(drawingvisitor);
//
//	compositions1.Accept(drawingvisitor);
//
//	compositions2.Accept(drawingvisitor);
//
//	compositions1 = compositions;
//
//	compositions1.Accept(drawingvisitor);
//
//	Figure *figure = compositions2.Clone();
//
//	static_cast<Compositions*>(figure)->Accept(drawingvisitor);
//
//	return 0;
//}