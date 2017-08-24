#include "Class.h"

Class::Class(Long capacity):lines(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->name = "";
}

Class::Class(Long x, Long y, Long width, Long height, Long capacity):lines(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	//클래스 이름 확인용
	this->name = "예비군";
}

Class::Class(Long x, Long y, Long width, Long height, string name, Long capacity) :lines(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->name = name;
}

Class::Class(const Class& source):lines(source.lines) {
	this->capacity = source.capacity;
	this->length = source.length;
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->name = source.name;
}
Class& Class::operator=(const Class& source) {
	this->lines = source.lines;
	this->capacity = source.capacity;
	this->length = source.length;
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->name = source.name;
	return *this;
}

Long Class::Add(Long startX, Long startY, Long endX, Long endY) {
	
	Line line(startX, startY, endX, endY);
	Long index = -1;

	if (this->length < 3) {
		index = this->lines.Store(this->length, line);
		this->length++;
	}
	return index;
}

Line& Class::GetAt(Long index) {
	return this->lines.GetAt(index);
}

Line& Class::operator [] (Long index) {
	return this->lines[index];
}

Line* Class::operator + (Long index) {
	return this->lines + index;
}

Class::~Class() {
}

/*
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

	Class object(100,150,20,30,"Class");
	object.Add(101, 102, 103, 104);
	Class objectCopy(object);
	Class objectCopy2 = objectCopy;

	cout << endl << object[0].GetStartX() << endl << endl;

	cout << objectCopy.GetLength() << " " << objectCopy.GetCapacity() << endl;
	cout << objectCopy2[0].GetStartX() << " " << objectCopy2[0].GetStartY() << " " << objectCopy2.GetAt(0).GetEndX() << endl;
	cout << objectCopy2 + 0 << endl;

	cout << object.GetX() << endl;
	cout << object.GetWidth() << endl;
	cout << object.GetY() << endl;
	cout << object.GetName() << endl;
	
	
	return 0;
}

// */
