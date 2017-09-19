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

void Selection::FindByArea(Diagram *diagram, CRect area) {

	Long i = 0;
	Long j;

	FigureComposite *composite;
	CRect rect;
	bool ret;
	Figure *figure;

	while (i < diagram->GetLength()) {
		//수정
		composite = static_cast<FigureComposite*>(diagram->GetAt(i));
		rect.left = composite->GetX();
		rect.top = composite->GetY();
		rect.right = composite->GetX() + composite->GetWidth();
		rect.bottom = composite->GetY() + composite->GetHeight();
		ret = rect.IntersectRect(area, rect);
		if (ret == true) {
			if (this->length < this->capacity) {
				this->figures.Store(this->length, composite);
			}
			else {
				this->figures.AppendFromRear(composite);
				this->capacity++;
			}
			this->length++;
		}

		j = 0;


		while (j < composite->GetLength()) {
			ret = false;

			figure = composite->GetAt(j);
			CPoint line1Start;
			CPoint line1End;
			CPoint line2Start;
			CPoint line2End;
			CPoint cross1;


			line1Start.x = figure->GetX();
			line1Start.y = figure->GetY();
			line1End.x = figure->GetX() + figure->GetWidth();
			line1End.y = figure->GetY() + figure->GetHeight();


			//범위안 라인찾기


			if (figure->GetX() >= area.left  &&  figure->GetY() >= area.top  &&  figure->GetX() <= area.right  &&   figure->GetY() <= area.bottom
				&& figure->GetX() + figure->GetWidth() >= area.left  &&  figure->GetY() + figure->GetHeight() >= area.top  &&
				figure->GetX() + figure->GetWidth() <= area.right  &&   figure->GetY() + figure->GetHeight() <= area.bottom) {
				ret = true;
			}
			//교차점 찾기

			if (ret == false) {//시작 클래스에서 선과 교차하는 면 찾기
							   //상단
				line2Start.x = area.left;
				line2Start.y = area.top;
				line2End.x = area.right;
				line2End.y = area.top;
				ret = this->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross1);
			}
			if (ret == false) {
				//좌측
				line2Start.x = area.left;
				line2Start.y = area.top;
				line2End.x = area.left;
				line2End.y = area.bottom;
				ret = this->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross1);
			}
			if (ret == false) {
				//우측
				line2Start.x = area.right;
				line2Start.y = area.top;
				line2End.x = area.right;
				line2End.y = area.bottom;
				ret = this->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross1);
			}
			if (ret == false) {
				//하단
				line2Start.x = area.left;
				line2Start.y = area.bottom;
				line2End.x = area.right;
				line2End.y = area.bottom;
				ret = this->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross1);
			}



			if (ret == true) {
				if (this->length < this->capacity) {
					this->figures.Store(this->length, figure);
				}
				else {
					this->figures.AppendFromRear(figure);
					this->capacity++;
				}
				this->length++;
			}

			j++;
		}
		i++;
	}
}
Long Selection::FindByPoint(Diagram *diagram, Long x, Long y) {

	FigureComposite *composite;
	Figure *figure = 0;
	bool ret;
	Long i = 0;
	Long j ;
	Long endX;
	Long endY;
	Long index = -1;


	while (i < diagram->GetLength() && index == -1) {
		endX = diagram->GetAt(i)->GetX() + diagram->GetAt(i)->GetWidth();
		endY = diagram->GetAt(i)->GetY() + diagram->GetAt(i)->GetHeight();
		if (diagram->GetAt(i)->GetX() <= x && endX >= x && diagram->GetAt(i)->GetY() <= y && endY >= y) {
			index = i;
		}
		if (index != -1) {
			if (this->length < this->capacity) {
				this->figures.Store(this->length, diagram->GetAt(index));
			}
			else {
				this->figures.AppendFromRear(diagram->GetAt(index));
				this->capacity++;
			}
			this->length++;
		}
		composite = static_cast<FigureComposite*>(diagram->GetAt(i));
		j = 0;
		ret = false;
		while (j < composite->GetLength() && ret != true && index == -1) {
			figure = composite->GetAt(j);

			CPoint line1Start;
			CPoint line1End;
			CPoint line2Start;
			CPoint line2End;
			CPoint cross1;


			line1Start.x = figure->GetX();
			line1Start.y = figure->GetY();
			line1End.x = figure->GetX() + figure->GetWidth();
			line1End.y = figure->GetY() + figure->GetHeight();
			if (ret == false) {//시작 클래스에서 선과 교차하는 면 찾기
							   //상단
				line2Start.x = x - 5;
				line2Start.y = y - 5;
				line2End.x = x + 5;
				line2End.y = y - 5;
				ret = this->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross1);
			}
			if (ret == false) {
				//좌측
				line2Start.x = x - 5;
				line2Start.y = y - 5;
				line2End.x = x - 5;
				line2End.y = y + 5;
				ret = this->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross1);
			}
			if (ret == false) {
				//우측
				line2Start.x = x + 5;
				line2Start.y = y - 5;
				line2End.x = x + 5;
				line2End.y = y + 5;
				ret = this->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross1);
			}
			if (ret == false) {
				//하단
				line2Start.x = x - 5;
				line2Start.y = y + 5;
				line2End.x = x + 5;
				line2End.y = y + 5;
				ret = this->FindCrossPoints(line1Start, line1End, line2Start, line2End, &cross1);
			}
			j++;
		}
		if (ret == true) {
			index = j;
			if (this->length < this->capacity) {
				this->figures.Store(this->length, figure);
			}
			else {
				this->figures.AppendFromRear(figure);
				this->capacity++;
			}
			this->length++;
		}
		i++;
	}
		return index;
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

bool Selection::FindCrossPoints(const CPoint& line1Start, const CPoint& line1End, const CPoint& line2Start, const CPoint& line2End, CPoint *crossPoint){
	double t;
	double s;
	bool ret = false;
	double under = (line2End.y - line2Start.y)*(line1End.x - line1Start.x) - (line2End.x - line2Start.x)*(line1End.y - line1Start.y);
	if (under != 0) {
		double _t = (line2End.x - line2Start.x)*(line1Start.y - line2Start.y) - (line2End.y - line2Start.y)*(line1Start.x - line2Start.x);
		double _s = (line1End.x - line1Start.x)*(line1Start.y - line2Start.y) - (line1End.y - line1Start.y)*(line1Start.x - line2Start.x);
		t = _t / under;
		s = _s / under;
		if (t >= 0.0 && t <= 1.0 && s >= 0.0 && s <= 1.0 && _t != 0 && _s != 0) {
			crossPoint->x = static_cast<LONG>(line1Start.x + t*(double)(line1End.x - line1Start.x));
			crossPoint->y = static_cast<LONG>(line1Start.y + t*(double)(line1End.y - line1Start.y));
			ret = true;
		}
	}
	return ret;
}