//SelfGeneralization.cpp

#include "SelfGeneralization.h"

SelfGeneralization::SelfGeneralization() :SelfRelation() {

}

SelfGeneralization::SelfGeneralization(Long x, Long y, Long width, Long height) :SelfRelation(x,y,width,height) {

}

SelfGeneralization::SelfGeneralization(const SelfGeneralization& source) : SelfRelation(source) {

}

SelfGeneralization& SelfGeneralization::operator=(const SelfGeneralization& source) {
	SelfRelation::operator=(source);
	return *this;
}

SelfGeneralization::~SelfGeneralization() {

}

Figure* SelfGeneralization::Clone() const {
	return new SelfGeneralization(*this);
}

void SelfGeneralization::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);//, cPaintDc);
}
//
//#include "ClassDiagramForm.h"
//#include <iostream>
//using namespace std;
//int main() {
//	ClassDiagramForm classDiagramForm;
//	SelfGeneralization object(10,20,30,40);
//	DrawingVisitor drawingVisitor;
//	CDC *cPatintDC  = 0;
//
//	SelfGeneralization object1;
//	object1 = object; 
//
//	Figure *figure = object1.Clone();
//
//	if (dynamic_cast<SelfGeneralization*>(figure)) {
//		cout << "셀프" << endl;
//	}
//
//	object.Accept(drawingVisitor, cPatintDC);
//	cout << "치환연산자" << endl;
//	object1.Accept(drawingVisitor, cPatintDC);
//
//	return 0;
//}