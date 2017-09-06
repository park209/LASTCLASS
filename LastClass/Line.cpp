//Line.cpp

#include "Line.h"

Line::Line() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

Line::~Line() {
}

Line::Line(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Line::Line(const Line& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
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

#include <iostream>
using namespace std;

void Line::Accept(Visitor& visitor, CDC *cPaintDc) {
	cout << "Line Accept" << endl;
	visitor.Visit(this, cPaintDc);
}


//#include <iostream>
//using namespace std;
//
//int main(int argc, char* argv[]) {
//
//	Line testLine0;
//	Line testLine1(10, 20, 30, 40);
//	cout << testLine1.GetX() << " " << testLine1.GetY() << " " << testLine1.GetWidth() << " " << testLine1.GetHeight() << endl;
//	
//	Line testLine2(testLine1);
//	cout << testLine2.GetX() << " " << testLine2.GetY() << " " << testLine2.GetWidth() << " " << testLine2.GetHeight() << endl;
//
//	Line testLine3(40, 30, 20, 10);
//	testLine2 = testLine3;
//	cout << testLine2.GetX() << " " << testLine2.GetY() << " " << testLine2.GetWidth() << " " << testLine2.GetHeight() << endl;
//
//	cout << &testLine2 << " " << testLine2.Clone() << endl;
//
//	return 0;
//}