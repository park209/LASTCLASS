//Diagram.cpp

#include "Diagram.h"

Diagram::Diagram(Long capacity) {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->length = 0;
	this->capacity = capacity;
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
	Long index = -1;
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

Figure* Diagram::GetAt(Long index) {
	return this->figures.GetAt(index);
}

Figure* Diagram::Clone() {
	return new Diagram(*this);
}


//#include <iostream>
//using namespace std;
//int main(int argc, char* argv[]) {
//	Class object1(10, 20, 30, 40);
//	cout << object1.GetX() << " " << object1.GetY() << " " << object1.GetWidth() << " " << object1.GetHeight() << endl;
//
//	Class object2;
//	cout << object2.GetX() << " " << object2.GetY() << " " << object2.GetWidth() << " " << object2.GetHeight() << endl;
//
//	object2 = object1;
//	cout << object2.GetX() << " " << object2.GetY() << " " << object2.GetWidth() << " " << object2.GetHeight() << endl;
//
//	Class object3(object1);
//	cout << object3.GetX() << " " << object3.GetY() << " " << object3.GetWidth() << " " << object3.GetHeight() << endl;
//
//	Long index = object1.Add(20, 20, 20, 20);
//	cout << index << endl;
//	index = object1.Add(10, 20, 30, 20);
//	cout << index << endl;
//
//	cout << object1.GetAt(1)->GetX() << object1.GetAt(1)->GetY() << object1.GetAt(1)->GetWidth() << object1.GetAt(1)->GetHeight() << endl;
//
//	return 0;
//}

#include <iostream>
using namespace std;
int main(int argc, char* argv[]) {
	Diagram object1;
	Long index;
	Long index1;
	Long index2;
	index = object1.Add(0, 0, 50, 40);

	cout << object1.GetAt(index)->GetX() << " " << object1.GetAt(index)->GetY() << " " << object1.GetAt(index)->GetWidth() << " " << object1.GetAt(index)->GetHeight() << endl;

	index1 = static_cast<Class*>(object1.GetAt(index))->Add(0, 0, 50,1);
	index2 = static_cast<Class*>(object1.GetAt(index))->Add(0, 0, 50, 30);

	cout << static_cast<Class*>(object1.GetAt(index))->GetAt(index1)->GetX() << " " << static_cast<Class*>(object1.GetAt(index))->GetAt(index1)->GetY() << " " <<
		static_cast<Class*>(object1.GetAt(index))->GetAt(index1)->GetWidth() << " " << static_cast<Class*>(object1.GetAt(index))->GetAt(index1)->GetHeight() << endl << endl;

	cout << static_cast<Class*>(object1.GetAt(index))->GetAt(index2)->GetX() << " " << static_cast<Class*>(object1.GetAt(index))->GetAt(index2)->GetY() << " " <<
		static_cast<Class*>(object1.GetAt(index))->GetAt(index2)->GetWidth() << " " << static_cast<Class*>(object1.GetAt(index))->GetAt(index2)->GetHeight() << endl << endl;
	cout << object1.GetCapacity() << " " << object1.GetLength() << endl;
	cout << static_cast<Class*>(object1.GetAt(index))->GetCapacity() << " " << static_cast<Class*>(object1.GetAt(index))->GetLength() << endl;

	Diagram object2;
	index = object2.Add(0, 0, 100, 100);
	cout << object2.GetAt(index)->GetX() << " " << object2.GetAt(index)->GetY() << " " << object2.GetAt(index)->GetWidth() << " " << object2.GetAt(index)->GetHeight() << endl;

	index1 = static_cast<Class*>(object2.GetAt(index))->Add(0, 0, 100, 10);
	index2 = static_cast<Class*>(object2.GetAt(index))->Add(0, 0, 100, 44);

	cout << static_cast<Class*>(object2.GetAt(index))->GetAt(index1)->GetX() << " " << static_cast<Class*>(object2.GetAt(index))->GetAt(index1)->GetY() << " " <<
		static_cast<Class*>(object2.GetAt(index))->GetAt(index1)->GetWidth() << " " << static_cast<Class*>(object2.GetAt(index))->GetAt(index1)->GetHeight() << endl << endl;

	cout << static_cast<Class*>(object1.GetAt(index))->GetAt(index2)->GetX() << " " << static_cast<Class*>(object1.GetAt(index))->GetAt(index2)->GetY() << " " <<
		static_cast<Class*>(object1.GetAt(index))->GetAt(index2)->GetWidth() << " " << static_cast<Class*>(object1.GetAt(index))->GetAt(index2)->GetHeight() << endl << endl;

	cout << object2.GetCapacity() << " " << object2.GetLength() << endl;

	cout << static_cast<Class*>(object2.GetAt(index))->GetCapacity() << " " << static_cast<Class*>(object2.GetAt(index))->GetLength() << endl;


	return 0;
}