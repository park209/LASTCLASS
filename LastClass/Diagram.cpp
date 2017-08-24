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
Class Diagram::GetAt(Long index) {
	return this->classes.GetAt(index);
}
/*
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {

	Diagram diagram(10);
	Long index = diagram.Add(1, 2, 5, 8);
	cout << index << endl << endl;

	cout << diagram[0].GetX() << " " << diagram[0].GetY() << " " << diagram[0].GetWidth() << " " << diagram[0].GetHeight() << endl;

	return 0;
}

// */