#include "Diagram.h"


Diagram::Diagram(Long capacity):classes(capacity) {
	this->capacity = capacity;
	this->length = 0;
}
Diagram::Diagram(const Diagram& source):classes(source.classes) {
	this->capacity = source.capacity;
	this->length = source.length;
}
Diagram& Diagram::operator=(const Diagram& source) {
	this->classes = source.classes;
	this->capacity = source.capacity;
	this->length = source.length;
	return *this;
}
Class& Diagram::operator[](Long index) {
	return this->classes[index];
}
Class* Diagram::operator + (Long index) {
	return this->classes + index;
}

Diagram::~Diagram() {
}

Long Diagram::Add(Long x, Long y, Long width, Long height) {
	Class object(x, y, width, height);
	Long index;
	if (this->length < this->capacity) {
		index = this->classes.Store(this->length, object);
	}
	else {
		index = this->classes.AppendFromRear(object);
		this->capacity++;
	}
	this->length++;
	return index;
}
Class& Diagram::GetAt(Long index) {
	return this->classes.GetAt(index);
}

/*
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	
	Diagram diagram(10);
	Long index = diagram.Add(100, 100, 300, 600);
	cout << index << endl << endl;

	cout << diagram[0].GetX() << " " << diagram[0].GetY() << " " << endl;

	cout << diagram[0].GetAt(0).GetStartX() << " " << diagram[0][0].GetStartY() << " " << diagram[0][0].GetEndX() << " " << diagram[0][0].GetEndY() << endl;
	cout << diagram[0].GetAt(1).GetStartX() << " " << diagram[0][1].GetStartY() << " " << diagram[0][1].GetEndX() << " " << diagram[0][1].GetEndY() << endl;

	Class classTest = diagram[0];
	cout << endl << classTest.GetX() << endl << endl;
	Line lineTest = classTest[0];
	cout << endl << lineTest.GetStartX() << endl << endl;

	cout << diagram.GetLength() << " " << diagram.GetCapacity() << endl;
	cout << diagram[0].GetX() << " " << diagram[0].GetY() << " " << diagram[0].GetWidth() << " " << diagram[0].GetHeight() << endl;

	return 0;
}

// */