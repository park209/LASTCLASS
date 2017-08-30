//Figure.cpp
#include "Figure.h"

Figure::Figure() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

Figure::Figure(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Figure::Figure(const Figure& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}

Figure& Figure::operator = (const Figure& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	
	return *this;
}

Figure::~Figure() {
}


