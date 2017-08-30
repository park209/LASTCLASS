//FigureComposite.cpp

#include "FigureComposite.h"

FigureComposite::FigureComposite(Long capacity) : figures(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

FigureComposite::FigureComposite(const FigureComposite& source) : figures(source.figures) {
	Long i = 0;
	Figure *figure = 0;

	while (i < source.length) {
		this->figures.Modify(i, (const_cast<FigureComposite&>(source)).figures[i]->Clone());
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
}


FigureComposite::~FigureComposite() {
}

//Long FigureComposite::Add(Figure *figure) {
//}

Long FigureComposite::Remove(Long index) {
	index = this->figures.Delete(index);
	this->length--;

	return index;
}

Figure* FigureComposite::GetAt(Long index) {
	return this->figures.GetAt(index);
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
//
//#include <iostream>
//using namespace std;
//
//int main(int argc, char* argv[]) {
//
//
//
//
//}