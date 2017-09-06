#include "Generalization.h"

Generalization::Generalization() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}


Generalization::Generalization(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Generalization::~Generalization() {

}

Generalization::Generalization(const Generalization& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}

Generalization& Generalization::operator=(const Generalization& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Generalization::Accept(Visitor& visitor ){//, CDC *cPaintDc) {
	visitor.Visit(this);//, cPaintDc);
}

Figure* Generalization::Clone() const {
	return new Generalization(*this);
}

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	Generalization generalization(20,30,40,50);

	Generalization generalization1(100, 100, 200, 300);

	DrawingVisitor drawingVisitor;

	Generalization generalization2(generalization1);

	generalization.Accept(drawingVisitor);

	generalization1.Accept(drawingVisitor);

	generalization2.Accept(drawingVisitor);

	generalization1 = generalization;

	generalization1.Accept(drawingVisitor);

	Figure *figure = generalization2.Clone();

	static_cast<Generalization*>(figure)->Accept(drawingVisitor);

	return 0;
}