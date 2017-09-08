//FigureComposite.cpp

#include "FigureComposite.h"
//#include "ArrayIterator.h"
#include "SmartPointer.h"
FigureComposite::FigureComposite(Long capacity) : figures(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

FigureComposite::FigureComposite(const FigureComposite& source) : figures(source.figures) {
	Long i = 0;
	while (i < source.length) {
		this->figures.Modify(i, (const_cast<FigureComposite&>(source)).figures[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

FigureComposite::~FigureComposite() {
}

FigureComposite& FigureComposite::operator = (const FigureComposite& source) {
	this->figures = source.figures;
	this->capacity = source.capacity;
	this->length = source.length;

	Long i = 0;
	while (i < source.length) {
		this->figures.Modify(i, (const_cast<FigureComposite&>(source)).figures[i]->Clone());
		i++;
	}
	return *this;
}

ArrayIterator<Figure*>* FigureComposite::CreateIterator() const {
	return new ArrayIterator<Figure*>(&this->figures);
}


//#include <iostream>
//using namespace std;
//
//int main(int argc, char* argv[]) {
//
//	return 0;
//}