//Line.cpp

#include "Line.h"

Line::Line() {
	this->startX = 0;
	this->startY = 0;
	this->endX = 0;
	this->endY = 0;
}

Line::Line(Long startX, Long startY, Long endX, Long endY) {
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
}
Line::Line(const Line& source) {
	this->startX = source.startX;
	this->startY = source.startY;
	this->endX = source.endX;
	this->endY = source.endY;
}

Line& Line::operator = (const Line& source) {
	this->startX = source.startX;
	this->startY = source.startY;
	this->endX = source.endX;
	this->endY = source.endY;
	return *this;
}

Line::~Line() {
}

/*
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

	Line line1(10, 10, 50, 50);

	cout << line1.GetStartX() << " " << line1.GetEndY() << endl;

}

// */