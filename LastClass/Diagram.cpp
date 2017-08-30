//Diagram.cpp

#include "Diagram.h"

Diagram::Diagram(Long capacity){
	this->capacity = capacity;
	this->length = 0;
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

Diagram::~Diagram() {
}

Diagram::Diagram(const Diagram& source) {
	this->figures = source.figures;
	Long i = 0;

	while (i < this->length) {
		this->figures.Modify(i, (const_cast<Diagram&>(source)).figures[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->length = source.length;
}

Diagram& Diagram::operator = (const Diagram& source) {
	this->figures = source.figures;
	Long i = 0;
	while (i < this->length) {
		this->figures.Modify(i, (const_cast<Diagram&>(source)).figures[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->length = source.length;

	return *this;
}

Long  Diagram::Add(Figure *figure) {
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

Long Diagram::Add(Long x, Long y, Long width, Long height) {
	Class object(x, y, width, height);
	Long index;

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

Long Diagram::Remove(Long index) {
	return this->figures.Delete(index);
}

Class* Diagram::GetAt(Long index) {
	return static_cast<Class*>(this->figures.GetAt(index));
}

Figure* Diagram::Clone() {
	return new Diagram(*this);
}

void Diagram::Accept(Visitor& visitor, CDC *cPaintDc) {
	//visitor.VisitDiagram(this, cPaintDc);
	SmartPointer<Figure*> smartPointer(this->CreateIterator());
	while (!smartPointer->IsDone()) {
		smartPointer->Current()->Accept(visitor, cPaintDc);
		smartPointer->Next();
	}
}

//
//#include <iostream>
//using namespace std;
//int main(int argc, char* argv[]) {
//	Diagram object1;
////	Diagram object2;
//	Long index;
////
//	index = object1.Add(0, 0, 50, 40);
//	index = object1.Add(0, 1, 50, 40);
//	index = object1.Add(0, 2, 50, 40);
//	index = object1.Add(0, 3, 50, 40);
////	cout << object1.GetCapacity() << " " << object1.GetLength() << endl;
////
////	index = object1.Add(1, 1, 100, 100);
////	cout << object2.GetCapacity() << " " << object2.GetLength() << endl;
////
////	index = object2.Add(1, 1, 222, 222);
////	cout << object2.GetCapacity() << " " << object2.GetLength() << endl;
////
////	cout << object2.GetAt(index)->GetX() << " " << object2.GetAt(index)->GetY() << " " << object2.GetAt(index)->GetWidth() << " " << object2.GetAt(index)->GetHeight() << endl;
////
////	Long index1 = static_cast<Class*>(object2.GetAt(index))->Add(0, 0, 50, 1);
////	index1 = static_cast<Class*>(object2.GetAt(index))->Add(0, 0, 44, 44);
////	index1 = static_cast<Class*>(object2.GetAt(index))->Add(0, 0, 33, 33);
////
////	cout << static_cast<Class*>(object2.GetAt(index))->GetAt(index1)->GetX() << " " << 
////		static_cast<Class*>(object2.GetAt(index))->GetAt(index1)->GetY() << " " << 
////		static_cast<Class*>(object2.GetAt(index))->GetAt(index1)->GetWidth() << " " << 
////		static_cast<Class*>(object2.GetAt(index))->GetAt(index1)->GetHeight() << endl;
////	cout << static_cast<Class*>(object2.GetAt(index))->GetCapacity() << " " << static_cast<Class*>(object2.GetAt(index))->GetLength() << endl;
////
////	cout << static_cast<Class*>(object1.GetAt(0))->GetCapacity() << " " << static_cast<Class*>(object1.GetAt(0))->GetLength() << endl;
////	cout << object1.GetCapacity() << " " << object1.GetLength() << endl;
////
//	SmartPointer<Figure*> ai(object1.CreateIterator());
//	for (ai->First(); !ai->IsDone(); ai->Next()) {
//		index = ai->Current()->GetY();
//		cout << index << endl;
//	}
//return 0;
//}