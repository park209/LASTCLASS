//Association.cpp
// ¿¬°üÈ­

#include "Association.h"

Association::Association(Long capacity) :Relation(capacity){
}

Association::Association(Long x, Long y, Long width, Long height):Relation(x,y,width,height) {
}

Association::~Association() {

}

Association::Association(const Association& source) :Relation(source){

}

Association& Association::operator=(const Association& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Association::Accept(Visitor& visitor, CDC *cPaintDc) { //, CDC *cPaintDc
	visitor.Visit(this, cPaintDc);
}

Figure* Association::Clone() const {
	return new Association(*this);
}
//
//#include <iostream>
//#include <afxwin.h>
//using namespace std;
//
//int main(int argc, char *argv[]) {
//
//	Association association(10);
//	CPoint cpoint;
//	cpoint.x = 100;
//	cpoint.y = 200;
//	association.Add(cpoint);
//	association.Add(cpoint);
//	association.Add(cpoint);
//	association.Add(cpoint);
//	association.Add(cpoint);
//	association.Add(cpoint);
//	association.Add(cpoint);
//	association.Add(cpoint);
//	association.Add(cpoint);
//	association.Add(cpoint);
//	association.Add(cpoint);
//	association.Add(cpoint);
//	association.Add(cpoint);
//	association.Add(cpoint);
//	association.Add(cpoint);
//	Long length = association.GetLength();
//	Long capacity = association.GetCapacity();
//
//	cout << length << " "  << capacity << endl;
//
//	Long i = 0;
//	Long x;
//	Long y;
//	while (i < length) {
//		x = association.GetAt(i).x;
//		y = association.GetAt(i).y;
//		cout << x << " " << y << endl;
//		i++;
//	}
//	i = 0;
//	cpoint.x = 200;
//	cpoint.y = 100;
//	while (i < length) {
//		association.Move(i, cpoint);
//		x = association.GetAt(i).x;
//		y = association.GetAt(i).y;
//		cout << x << " " << y << endl;
//		i++;
//	}
//	i = 0;
//	while (i < length) {
//		association.Remove(i);
//		i++;
//	}
//	length = association.GetLength();
//	capacity = association.GetCapacity();
//	cout << length << " " << capacity << endl;
//	return 0;
//}
