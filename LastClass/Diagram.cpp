//Diagram.cpp

#include "Diagram.h"
#include "Class.h"
#include "MemoBox.h"
#include "SmartPointer.h"

Diagram::Diagram(Long capacity):FigureComposite(capacity) {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

Diagram::~Diagram() {
}

Diagram::Diagram(const Diagram& source):FigureComposite(source) {
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

Figure* Diagram::operator [] (Long index) {
	return this->figures[index];
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

Long Diagram::AddClass(Long x, Long y, Long width, Long height) {
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
Long Diagram::AddMemoBox(Long x, Long y, Long width, Long height) {
	MemoBox object(x, y, width, height);
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

Figure* Diagram::FindItem(Long x, Long y) {
	SmartPointer<Figure*> smartPointer(this->CreateIterator());//다이어그램 배열 반복자
	Figure *figure = 0;
	Long endX;
	Long endY;
	Long index = -1;
	smartPointer->First();
	while (!smartPointer->IsDone() && index != 0) {
		endX = smartPointer->Current()->GetX() + smartPointer->Current()->GetWidth();
		endY = smartPointer->Current()->GetY() + smartPointer->Current()->GetHeight();
		if (smartPointer->Current()->GetX() <= x && endX >= x && smartPointer->Current()->GetY() <= y && endY >= y) {
			figure = smartPointer->Current();
			index = 0;
		}
		smartPointer->Next();
	}
	if (index == 0) {
		SmartPointer<Figure*> smartPointer_(static_cast<Class*>(figure)->CreateIterator()); //클래스 배열 반복자
		for (smartPointer_->First(); !smartPointer_->IsDone(); smartPointer_->Next()) {
			if (smartPointer_->Current()->GetX() <= x && smartPointer_->Current()->GetX() + smartPointer_->Current()->GetWidth() >= x
				&& smartPointer_->Current()->GetY() <= y   && smartPointer_->Current()->GetY() + smartPointer_->Current()->GetHeight() >= y) {
				figure = smartPointer_->Current();
			}
		}
	}
	return figure;
}



Long Diagram::Remove(Long index) {
	return this->figures.Delete(index);
}

Figure* Diagram::GetAt(Long index) {
	return static_cast<Figure*>(this->figures.GetAt(index));
}

Figure* Diagram::Clone() const {
	return new Diagram(*this);
}


void Diagram::Accept(Visitor& visitor, CDC *cPaintDc) {
	//cout << "Diagram Accept" << endl;
	SmartPointer<Figure*> smartPointer(this->CreateIterator());
	while (!smartPointer->IsDone()) {
		if (dynamic_cast<Class*>(smartPointer->Current())) {
			dynamic_cast<Class*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		if(dynamic_cast<MemoBox*>(smartPointer->Current())){
			dynamic_cast<MemoBox*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		smartPointer->Next();
	}
}

//
//#include <iostream>
//using namespace std;
//int main(int argc, char* argv[]) {
//	Diagram object0;
//	object0.AddClass(10, 20, 30, 40);
//	object0.AddMemoBox(50, 60, 70, 80);
//	cout << "디폴트생성자, 매개변수생성자2개" << endl;
//	if (dynamic_cast<MemoBox*>(object0.GetAt(1))) {
//		cout << dynamic_cast<MemoBox*>(object0.GetAt(1))->GetX() << dynamic_cast<MemoBox*>(object0.GetAt(1))->GetY() <<
//			dynamic_cast<MemoBox*>(object0.GetAt(1))->GetWidth() << dynamic_cast<MemoBox*>(object0.GetAt(1))->GetHeight() << endl;
//	}
//	cout << object0.GetLength() << endl;
//	
//	return 0;
//}