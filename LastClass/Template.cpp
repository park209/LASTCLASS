#include "Template.h"



Template::Template():Figure() {

}
Template::Template(Long x, Long  y, Long width, Long height):Figure(x,y,width,height) {

}
Template::Template(const Template& source):Figure(source) {

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