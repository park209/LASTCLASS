#include "MemoLine.h"

MemoLine::MemoLine() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}


MemoLine::MemoLine(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

MemoLine::~MemoLine() {

}

MemoLine::MemoLine(const MemoLine& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}

MemoLine& MemoLine::operator=(const MemoLine& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void MemoLine::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);//, cPaintDc);
}


Figure* MemoLine::Clone() const {
	return new MemoLine(*this);
}