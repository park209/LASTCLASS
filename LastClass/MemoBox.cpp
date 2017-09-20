//MemoBox.cpp

#include "MemoBox.h"
#include "MemoLine.h"
#include "SmartPointer.h"

MemoBox::MemoBox(Long capacity) : FigureComposite(capacity) {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}
MemoBox::MemoBox(Long x, Long y, Long width, Long height) : FigureComposite(10) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}
MemoBox::MemoBox(const MemoBox& source) : FigureComposite(source) {
	
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}
MemoBox::~MemoBox() {
}

Long MemoBox::Add(Long x, Long y, Long width, Long height) {
	MemoLine object(x, y, width, height);
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

Figure* MemoBox::GetAt(Long index) {
	return static_cast<Figure*>(this->figures.GetAt(index));
}


Long MemoBox::Remove(Long index) {

	this->length--;
	this->capacity--;

	return this->figures.Delete(index);
}

Figure* MemoBox::Clone() const {
	return new MemoBox(*this);
}

MemoBox& MemoBox::operator=(const MemoBox& source) {
	this->figures = source.figures;
	Long i = 0;

	while (i < source.length) {
		this->figures.Modify(i, (const_cast<MemoBox&>(source)).figures[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	return *this;
}

Figure* MemoBox::operator[](Long index) {
	return this->figures[index];
}

Long MemoBox::Add(Figure *figure) {
	Long index;
	if (this->length < this->capacity) {
		index = this->figures.Store(this->length, figure);
	}
	else {
		index = this->figures.AppendFromRear(figure);
		this->capacity++;
	}
	this->length++;
	return  index;
}

void MemoBox::Accept (Visitor& visitor, CDC *cPaintDc) { 
	visitor.Visit(this, cPaintDc);
	SmartPointer<Figure*> smartPointer(this->CreateIterator());
	while (!smartPointer->IsDone()) {
		if (dynamic_cast<MemoLine*>(smartPointer->Current())) {
			dynamic_cast<MemoLine*>(smartPointer->Current())->Accept(visitor, cPaintDc);  //, CPointDc
		}
		smartPointer->Next();
	}
}


