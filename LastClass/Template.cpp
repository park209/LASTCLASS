//Template.h

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
Figure* Template::Clone() const {
	return new Template(*this);
}
void Template::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);
}