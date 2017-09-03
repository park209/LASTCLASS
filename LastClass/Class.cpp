//Class.cpp

#include "Class.h"

Class::Class(Long capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

Class::Class(Long x, Long y, Long width, Long height) {
	this->capacity = 8;
	this->length = 0;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Class::Class(const Class& source) {
	this->figures = source.figures;
	Long i = 0;
	while (i < source.length) {
		this->figures.Modify(i, (const_cast<Class&>(source)).figures[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}

Class::~Class() {
}

Class& Class::operator = (const Class& source) {
	this->figures = source.figures;
	Long i = 0;
	while (i < source.length) {
		this->figures.Modify(i, (const_cast<Class&>(source)).figures[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;

	return *this;
}

Figure* Class::operator [] (Long index) {
	return this->figures[index];
}

Long Class::Add(Figure *figure) {
	Long index;
	if (this->length < this->capacity) {
		index = this->figures.Store(this->length, figure);
	}
	else {
		index = this->figures.AppendFromRear(figure);
		this->capacity++;
	}
	this->length++;

	return index;
}

Long Class::Add(Long x, Long y, Long width, Long height) {
	Long index;
	Line object(x, y, width, height);

	if (this->length < this->capacity) {
		index = this->figures.Store(this->length, object.Clone());
	}
	else {
		index = this->figures.AppendFromRear(object.Clone());
		this->capacity++;
	}
	this->length++;

	return index;
}

Long Class::Remove(Long index) {
	return this->figures.Delete(index);
}

Line* Class::GetAt(Long index) { 
	return static_cast<Line*>(this->figures.GetAt(index));
}

Figure* Class::Clone() const{
	return new Class(*this);
}

#include <iostream>
using namespace std;

void Class::PrintLine(SmartPointer<Figure*>& index) {
	for (index->First(); !index->IsDone(); index->Next()) {
		cout << index->Current()->GetX() << " " << index->Current()->GetY() << endl;
	}
}


void Class::Accept(Visitor& visitor, CDC *cPaintDc) {
	cout << "Class Accept" << endl;
	visitor.Visit(this, cPaintDc);
	SmartPointer<Figure*> smartPointer(this->CreateIterator());
	while (!smartPointer->IsDone()) {
		static_cast<Line*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		smartPointer->Next();
	}
}


//#include <iostream>
//using namespace std;
//
//int main(int argc, char* argv[]) {
//	Class testClass0;
//	Class testClass1(10, 20, 30, 40);
//	cout << testClass1.GetX() << " " << testClass1.GetY() << " " << testClass1.GetWidth() << " " << testClass1.GetHeight() << endl;
//
//	Class testClass2(testClass1);
//	cout << testClass2.GetX() << " " << testClass2.GetY() << " " << testClass2.GetWidth() << " " << testClass2.GetHeight() << endl;
//
//	Class testClass3(40, 30, 20, 10);
//	testClass2 = testClass3;
//	cout << testClass2.GetX() << " " << testClass2.GetY() << " " << testClass2.GetWidth() << " " << testClass2.GetHeight() << endl;
//
//	Line testLine0(10, 10, 10, 10);
//	testClass1.Add(dynamic_cast<Figure*>(&testLine0)); //static_castµµ µÊ. ¹¹°¡ ¸Â´Â°Å? // testLine0.Clone()
//	cout << testClass1.GetAt(0)->GetX() << " " << testClass1.GetAt(0)->GetY() << " " << testClass1.GetAt(0)->GetWidth() << " " << testClass1.GetAt(0)->GetHeight() << endl;
//
//	Long index = testClass1.Add(50, 20, 20, 20);
//	cout << testClass1[index]->GetX() << " " << testClass1[index]->GetY() << " " << testClass1[index]->GetWidth() << " " << testClass1[index]->GetHeight() << endl;
//	index = testClass1.Add(60, 20, 20, 20);
//	cout << testClass1.GetAt(index)->GetX() << " " << testClass1.GetAt(index)->GetY() << " " << testClass1.GetAt(index)->GetWidth() << " " << testClass1.GetAt(index)->GetHeight() << endl;
//
//	index = testClass1.Remove(1);
//	if (index == -1) {
//		cout << "»èÁ¦µÊ" << endl;
//	}
//
//
//	return 0;
//}

