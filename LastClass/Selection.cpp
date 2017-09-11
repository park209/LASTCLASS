#include  "Selection.h"
#include "Diagram.h"

Selection::Selection(Long capacity):FigureComposite(capacity) {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}
Selection::Selection(const Selection& source) : FigureComposite(source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}
Selection::~Selection() {
}
Selection& Selection::operator=(const Selection& source) {
	this->figures = source.figures;
	Long i = 0;
	while (i < source.length) {
		this->figures.Modify(i, (const_cast<Selection&>(source)).figures[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;

	return *this;
}

Long Selection::Add(Figure *figure) {
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


Long Selection::Remove(Long index) {
	return this->figures.Delete(index);
}

Figure* Selection::Clone() const {
	return new Selection(*this);
}

Figure* Selection::GetAt(Long index) {
	return static_cast<Figure*>(this->figures.GetAt(index));
}
void Selection::DeleteAllItems() {
	

	while (this->length != 0){
		this->figures.Modify(this->length -1 , 0);
		this->length--;
		
	}

}

void Selection::Find(Diagram *diagram, CRect area) {
	
	Long i = 0;
	Long j;
	FigureComposite *composite;
	CRect rect;
	bool ret;
	Figure *figure;

	while (i < diagram->GetLength()) {
		composite = dynamic_cast<FigureComposite*>(diagram->GetAt(i));
		rect.left = composite->GetX();
		rect.top = composite->GetY();
		rect.right = composite->GetX() + composite->GetWidth();
		rect.bottom = composite->GetY() + composite->GetHeight();
		ret = rect.IntersectRect(area, rect);
		if (ret == true) {
			this->Add(composite);
		}
		i++;
		//j = 0;
		//if (j < composite->GetLength()) {
		//	figure = composite->GetAt(j);

		//}
	}
	
}

//#include "Diagram.h"
//#include "Class.h"
//#include "MemoBox.h"
//#include "Line.h"
//#include "Generalization.h"
//#include "Template.h"
//
//#include <iostream>
//using namespace std;
//int main(int argc, char* argv[]) {
//		Diagram object0;
//		object0.AddClass(10, 20, 30, 40);
//		dynamic_cast<Class*>(object0.GetAt(0))->Add(20, 30, 40, 40);
//		dynamic_cast<Class*>(object0.GetAt(0))->AddGeneralization(40, 50, 10, 10);
//		dynamic_cast<Class*>(object0.GetAt(0))->AddTemplate(13, 17, 10, 10);
//	    object0.AddMemoBox(50, 60, 70, 80);
//
//		Selection object1;
//		object1.Add(object0.GetAt(0));
//		object1.Add(dynamic_cast<Class*>(object0.GetAt(0))->GetAt(0));
//		object1.Add(dynamic_cast<Class*>(object0.GetAt(0))->GetAt(1));
//		object1.Add(dynamic_cast<Class*>(object0.GetAt(0))->GetAt(2));
//		object1.Add(object0.GetAt(1));
//
//		
//		cout << dynamic_cast<MemoBox*>(object1.GetAt(4))->GetX() << dynamic_cast<MemoBox*>(object1.GetAt(4))->GetY() << dynamic_cast<MemoBox*>(object1.GetAt(4))->GetWidth() <<
//			dynamic_cast<MemoBox*>(object1.GetAt(4))->GetHeight() << endl;
//
//		return 0;
//
//}