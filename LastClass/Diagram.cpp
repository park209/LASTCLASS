//Diagram.cpp

#include "Diagram.h"

Diagram::Diagram(Long capacity) {
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

Long Diagram::Find(Long x, Long y) {
	Long i = 0;
	Long j = 0;
	Long endX;
	Long endY;
	Long index = -1;
	while (i < this->GetLength() && index == -1) {
		endX = this->figures[i]->GetX() + this->figures[i]->GetWidth();
		endY = this->figures[i]->GetY() + this->figures[i]->GetHeight();
		if (this->figures[i]->GetX() <= x&&endX >= x&&this->figures[i]->GetY() <= y&&endY >= y) {
			index = i;
		}
		i++;
	}
	return index;

}

Long Diagram::Remove(Long index) {
	return this->figures.Delete(index);
}

Class* Diagram::GetAt(Long index) {
	return static_cast<Class*>(this->figures.GetAt(index));
}

Figure* Diagram::Clone() const {
	return new Diagram(*this);
}

#include <iostream>
using namespace std;

void Diagram::PrintClass(SmartPointer<Figure*>& index) {
	for (index->First(); !index->IsDone(); index->Next()) {
		static_cast<Class*>(index->Current());
		cout << index->Current()->GetX() << " " << index->Current()->GetY() << endl;
	}
}

void Diagram::Accept(Visitor& visitor, CDC *cPaintDc) {
	cout << "Diagram Accept" << endl;
	SmartPointer<Figure*> smartPointer(this->CreateIterator());
	while (!smartPointer->IsDone()) {
		static_cast<Class*>(smartPointer->Current())->Accept(visitor,cPaintDc);
		smartPointer->Next();
	}
}


//#include <iostream>
//using namespace std;
//int main(int argc, char* argv[]) {
//	Diagram object0;
//	object0.Add(10, 20, 30, 40);
//	object0.Add(Class(20, 30, 40, 50).Clone());
//	cout << "디폴트생성자, 매개변수생성자2개" << endl;
//
//	Diagram object1(object0);
//	cout << "Copy constructor" << endl;
//
//	Long i = 0;
//	while (i < object1.GetLength()) {
//		cout << object1.GetAt(i)->GetX() << " " << object1.GetAt(i)->GetY() << " " << object1.GetAt(i)->GetWidth() << " " << object1.GetAt(i)->GetHeight() << endl;
//		i++;
//	}
//	cout << static_cast<Class*>(object1.GetAt(0))->GetCapacity() << " " << static_cast<Class*>(object1.GetAt(0))->GetLength() << endl;
//	cout << object1.GetCapacity() << " " << object1.GetLength() << endl;
//
//	cout << "지금까지한거 위에꺼 확인" << endl << endl << endl;
//
//	object0.GetAt(0)->Add(0, 0, 50, 50);
//	static_cast<Class*>(object0[0])->Add(0, 0, 44, 44);
//	static_cast<Class*>(object0[1])->Add(0, 0, 33, 33);
//
//	Long j;
//	i = 0;
//	while (i < object0.GetLength()) {
//		j = 0;
//		while (j < object0.GetAt(i)->GetLength()) {
//			cout << object0.GetAt(i)->GetAt(j)->GetX() << " " <<
//				object0.GetAt(i)->GetAt(j)->GetY() << " " <<
//				object0.GetAt(i)->GetAt(j)->GetWidth() << " " <<
//				object0.GetAt(i)->GetAt(j)->GetHeight() << endl;
//			j++;
//		}
//		cout << static_cast<Class*>(object0.GetAt(i))->GetCapacity() << " " << static_cast<Class*>(object0.GetAt(i))->GetLength() << endl;
//		i++;
//	}
//	cout << "라인까지넣은거 확인" << endl << endl;
//
//	//ArrayIterator<Figure*>* testIterator = object1.CreateIterator();
//	//object1.PrintClass(testIterator);
//	//delete testIterator;
//	/////////////////////////////위아래 두개는 스마트포인터 안쓴거
//	//ArrayIterator<Figure*>* testIterator2 = object1.GetAt(0)->CreateIterator();
//	//object1.GetAt(0)->PrintLine(testIterator2);
//	//delete testIterator2;
//
//	SmartPointer<Figure*> testIterator(object1.CreateIterator());
//	object1.PrintClass(testIterator);
//	//////////////////////////////////////위아래 두개는 스마트포인터 쓴거
//	SmartPointer<Figure*> testIterator2(object1.GetAt(0)->CreateIterator());
//	object1.GetAt(0)->PrintLine(testIterator2);
//
//	cout << endl << "iterator 확인 끝" << endl << "visitor 확인시작" << endl << endl;
//
//	DrawingVisitor testVisitor;
//	object1.Accept(testVisitor);                         //Diagram Accept
//	//object1.GetAt(0)->Accept(testVisitor);             //Class Accept
//	//object1.GetAt(0)->GetAt(0)->Accept(testVisitor);   //Line Accept  //Console Drawing 확인 끝 2017_09_01 pm3:27 // Text 쪽 시작 전 백업
//	
//	return 0;
//}