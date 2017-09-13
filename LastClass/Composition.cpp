#include "Composition.h"

Composition::Composition() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}


Composition::Composition(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Composition::~Composition() {

}

Composition::Composition(const Composition& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}

Composition& Composition::operator=(const Composition& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Composition::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);//, cPaintDc);
}


Figure* Composition::Clone() const {
	return new Composition(*this);
}

//#include <iostream>
//using namespace std;
//
//int main(int argc, char *argv[]) {
//	Composition composition(20,30,40,50);
//
//	Composition composition1(100, 100, 200, 300);
//
//	DrawingVisitor drawingvisitor;
//
//	Composition composition2(composition1);
//
//	composition.Accept(drawingvisitor);
//
//	composition1.Accept(drawingvisitor);
//
//	composition2.Accept(drawingvisitor);
//
//	composition1 = composition;
//
//	composition1.Accept(drawingvisitor);
//
//	Figure *figure = composition2.Clone();
//
//	static_cast<Composition*>(figure)->Accept(drawingvisitor);
//
//	return 0;
//}