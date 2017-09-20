//Line.cpp

#include "Line.h"

Line::Line():Figure(){

}

Line::~Line(){
}

Line::Line(Long x, Long y, Long width, Long height) :Figure(x,y,width,height){
}

Line::Line(const Line& source):Figure(source) {
}

Line& Line::operator = (const Line& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;

	return *this;
}

Figure* Line::Clone() const {
	return new Line(*this);
}

void Line::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);
}


Figure* Line::Move(Long distanceX, Long distanceY) {
	Figure::Move(distanceX, distanceY);
	return this;
}