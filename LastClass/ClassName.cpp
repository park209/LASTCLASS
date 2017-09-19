//ClassName.cpp

#include "ClassName.h"

ClassName::ClassName() : Figure() {
}

ClassName::~ClassName() {
}

ClassName::ClassName(Long x, Long y, Long width, Long height, string content) : Figure(x, y, width, height, content) {
}

ClassName::ClassName(const ClassName& source) : Figure(source) {
}

ClassName& ClassName::operator = (const ClassName& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->content = source.content;

	return *this;
}

Figure* ClassName::Clone() const {
	return new ClassName(*this);
}

void ClassName::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);
}


//
//#include "ClassName.h"
//#include <iostream>
//using namespace std;
//
//int main(int argc, char* argv[]) {
//
//	ClassName testLine0;
//	ClassName testLine1(10, 20, 30, 40);
//	cout << testLine1.GetX() << " " << testLine1.GetY() << " " << testLine1.GetWidth() << " " << testLine1.GetHeight() << endl;
//	
//	ClassName testLine2(testLine1);
//	cout << testLine2.GetX() << " " << testLine2.GetY() << " " << testLine2.GetWidth() << " " << testLine2.GetHeight() << endl;
//
//	ClassName testLine3(40, 30, 20, 10);
//	testLine2 = testLine3;
//	cout << testLine2.GetX() << " " << testLine2.GetY() << " " << testLine2.GetWidth() << " " << testLine2.GetHeight() << endl;
//
//	Figure *figure = testLine3.Clone();
//
//	cout << dynamic_cast<ClassName*>(figure)->GetX() << " " << endl;
//
//	return 0;
//}