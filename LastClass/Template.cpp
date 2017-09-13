#include "Template.h"



Template::Template() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}
Template::Template(Long x, Long  y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}
Template::Template(const Template& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}
Template::~Template() {
}
Template& Template::operator= (const Template& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}
void Template::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);
}

Figure* Template::Clone() const {
	return new Template(*this);
}


//#include <iostream>
//using namespace std;
//
//int main(int argc, char *argv[]) {
//
//	Template object(10,20,30,40);
//	DrawingVisitor visitor;
//	object.Accept(visitor);
//	Template object1(object);
//	object1.Accept(visitor);
//
//	Template object3;
//	object3 = object;
//	object3.Accept(visitor);
//
//	Figure *figure = object.Clone();
//
//	static_cast<Template*>(figure)->Accept(visitor);
//
//	return 0;
//}