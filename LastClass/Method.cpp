//Method.cpp

#include "Method.h"

Method::Method() : Figure() {
}

Method::~Method() {
}

Method::Method(Long x, Long y, Long width, Long height, string content) : Figure(x, y, width, height, content) {
}

Method::Method(const Method& source) : Figure(source) {
}

Method& Method::operator = (const Method& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->content = source.content;

	return *this;
}

Figure* Method::Clone() const {
	return new Method(*this);
}

void Method::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);
}

//#include <iostream>
//using namespace std;
//
//int main(int argc, char *argv[]) {
//	Method temp1;
//
//	return 0;
//}
//
//#include "Method.h"
//#include <iostream>
//using namespace std;
//
//int main(int argc, char* argv[]) {
//
//	Method testLine0;
//	Method testLine1(10, 20, 30, 40);
//	cout << testLine1.GetX() << " " << testLine1.GetY() << " " << testLine1.GetWidth() << " " << testLine1.GetHeight() << endl;
//	
//	Method testLine2(testLine1);
//	cout << testLine2.GetX() << " " << testLine2.GetY() << " " << testLine2.GetWidth() << " " << testLine2.GetHeight() << endl;
//
//	Method testLine3(40, 30, 20, 10);
//	testLine2 = testLine3;
//	cout << testLine2.GetX() << " " << testLine2.GetY() << " " << testLine2.GetWidth() << " " << testLine2.GetHeight() << endl;
//
//	Figure *figure = testLine3.Clone();
//
//	cout << dynamic_cast<Method*>(figure)->GetX() << " " << endl;
//
//	return 0;
//}
