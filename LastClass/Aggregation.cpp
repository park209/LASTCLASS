//Aggregation.cpp
//С§Че

#include "Aggregation.h"

Aggregation::Aggregation(Long capacity):Relation(capacity) {
}

Aggregation::Aggregation(Long x, Long y, Long width, Long height) : Relation(x, y, width, height) {
}

Aggregation::~Aggregation() {

}

Aggregation::Aggregation(const Aggregation& source):Relation(source){
}

Aggregation& Aggregation::operator=(const Aggregation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Aggregation::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this,cPaintDc);//, cPaintDc);
}

Figure* Aggregation::Clone() const {
	return new Aggregation(*this);
}

#include <iostream>
#include <afxwin.h>
using namespace std;

int main(int argc, char *argv[]) {
	Aggregation object;
	Long capacity = object.GetCapacity();
	Long length = object.GetLength();
	cout << capacity << " " << length << endl;
	CPoint cpoint;
	cpoint.x = 100;
	cpoint.y = 100;
	Long i = 0;
	while (i < 100) {
		object.Add(cpoint);
		i++;
	}
	capacity = object.GetCapacity();
	length = object.GetLength();
	cout << endl << endl << length << " " << capacity << endl;
	i = 0;
	Long x;
	Long y;
	CPoint cpoint1;
	while (i < length) {
		cpoint1 = object.GetAt(i);
		x = cpoint1.x;
		y = cpoint1.y;
		cout << x << " " << y << endl;
		i++;
	}
	return 0;
}