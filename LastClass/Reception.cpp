//Reception.cpp

#include "Reception.h"

#include <iostream>
using namespace std;

Reception::Reception() : Figure() {
}

Reception::~Reception() {
}

Reception::Reception(Long x, Long y, Long width, Long height, string content) : Figure(x, y, width, height, content) {
}

Reception::Reception(const Reception& source) : Figure(source) {
}

Reception& Reception::operator = (const Reception& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->content = source.content;

	return *this;
}

Figure* Reception::Clone() const {
	return new Reception(*this);
}


//void Reception::Accept(Visitor& visitor, CDC *cPaintDc) {
//   //cout << "Reception Accept" << endl;
//   //visitor.Visit(this, cPaintDc);
//}


//
//int main(int argc, char* argv[]) {
//
//	Reception testReception0;
//	cout << testReception0.GetX() << ' ' << testReception0.GetY() << ' ' << testReception0.GetWidth() << ' ' << testReception0.GetHeight() << ' ' <<  testReception0.GetContent() << endl;
//
//	Reception testReception1(10, 20, 30, 40, " ¸®¼Á¼Ç");
//	cout << testReception1.GetX() << " " << testReception1.GetY() << " " << testReception1.GetWidth() << " " << testReception1.GetHeight() << testReception1.GetContent() << endl;
//
//	Reception testReception2(testReception1);
//	cout << testReception2.GetX() << " " << testReception2.GetY() << " " << testReception2.GetWidth() << " " << testReception2.GetHeight() << testReception2.GetContent() << endl;
//
//	Reception testReception3(40, 30, 20, 10, " ÀÎ¼Á¼Ç");
//	testReception2 = testReception3;
//	cout << testReception2.GetX() << " " << testReception3.GetY() << " " << testReception3.GetWidth() << " " << testReception3.GetHeight() << testReception3.GetContent() << endl;
//
//	Figure * figure = testReception3.Clone();
//	cout << dynamic_cast<Reception*>(figure)->GetX() << " " << dynamic_cast<Reception*>(figure)->GetY() << " " << dynamic_cast<Reception*>(figure)->GetWidth() << " " << dynamic_cast<Reception*>(figure)->GetHeight() << dynamic_cast<Reception*>(figure)->GetContent() << endl;
//
//	return 0;
//}