#include "Class.h"

Class::Class() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}
Class::Class(const Class& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}
Class&Class::operator=(const Class& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}
Class::Class(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}
Class::~Class() {
}


/*
#include <iostream>
using namespace std;
/*
int main(int argc, char* argv[]) {
	Class object;
	cout << object.GetX() << endl;
	return 0;
}

// */