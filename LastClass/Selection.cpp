#include  "Selection.h"
#include "Diagram.h"
#include "Relation.h"
#include "Finder.h"
#include "SelfRelation.h"
#include "Class.h"
#include "Template.h"
#include "HistoryGraphic.h"
Selection::Selection(Long capacity) :FigureComposite(capacity) {
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
	this->content = source.content;
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

Long Selection::Remove(Diagram *diagram, Figure *figure) {
	Long i = 0;
	Long index = -1;
	FigureComposite *figures = 0;
	while (i < diagram->GetLength() && figure != diagram->GetAt(i)) {
		i++;
	}
	if (i < diagram->GetLength()) {
		index = i;
		diagram->Remove(index);
	}

	i = 0;
	Long j;
	while (i < diagram->GetLength() && index == -1) {
		j = 0;
		figures = static_cast<FigureComposite*>(diagram->GetAt(i));
		while (j < figures->GetLength() && figure != figures->GetAt(j)) {
			j++;
		}
		if (j < figures->GetLength()) {
			index = j;
			figures->Remove(index);
		}
		i++;
	}

	this->figures.Delete(this->length - 1);
	this->length--;
	this->capacity--;
	return index;
}

Long Selection::Remove(Long index) {
	this->capacity--;
	this->length--;
	return this->figures.Delete(index);
}

Figure* Selection::Clone() const {
	return new Selection(*this);
}

Figure* Selection::GetAt(Long index) {
	return static_cast<Figure*>(this->figures.GetAt(index));
}
void Selection::DeleteAllItems() {
	while (this->length != 0) {
		this->figures.Delete(this->length - 1);
		this->length--;
		this->capacity--;
	}
}

void Selection::SelectByArea(Diagram *diagram, CRect area) {

	Finder finder;
	Long i = 0;
	Long j;
	Long k;

	FigureComposite *composite;
	CRect rect;
	bool ret = false;
	Relation *relation;

	while (i < diagram->GetLength()) {
		//수정
		composite = static_cast<FigureComposite*>(diagram->GetAt(i));
		rect.left = composite->GetX();
		rect.top = composite->GetY();
		rect.right = composite->GetX() + composite->GetWidth();
		rect.bottom = composite->GetY() + composite->GetHeight();

		ret = finder.FindRectangleByArea(rect, area);

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
			if (dynamic_cast<Relation*>(composite->GetAt(j))) {

				relation = static_cast<Relation*>(composite->GetAt(j));

				CPoint lineStart(relation->GetX(), relation->GetY());
				CPoint lineEnd;

				ret = false;
				k = 0;

				while (k < relation->GetLength() && ret == false) {
					lineEnd.x = relation->GetAt(k).x;
					lineEnd.y = relation->GetAt(k).y;
					ret = finder.FindLineByArea(lineStart, lineEnd, area);
					lineStart.x = lineEnd.x;
					lineStart.y = lineEnd.y;
					k++;
				}

				lineEnd.x = relation->GetWidth() + relation->GetX();
				lineEnd.y = relation->GetHeight() + relation->GetY();

				if (ret == false) {
					ret = finder.FindLineByArea(lineStart, lineEnd, area);
				}

				if (ret == true) {
					if (this->length < this->capacity) {
						this->figures.Store(this->length, relation);
					}
					else {
						this->figures.AppendFromRear(relation);
						this->capacity++;
					}
					this->length++;
				}
			}
			j++;
		}
		i++;
	}
}
Long Selection::SelectByPoint(Long x, Long y) {
	Finder finder;
	CRect rect;
	FigureComposite *composite;
	Relation *relation = 0;
	SelfRelation *selfRelation = 0;
	bool ret = false;
	Long i = 0;
	Long j = 0;
	Long index = -1;
	CPoint lineStart;
	CPoint lineEnd;
	bool squareFace = false;

	while (i < this->GetLength() && index == -1) {
		if (dynamic_cast<Relation*>(this->GetAt(i))) {
			relation = static_cast<Relation*>(this->GetAt(i));


			CRect rect(relation->GetX() - 10, relation->GetY() - 10, relation->GetX() + 10, relation->GetY() + 10);
			if (finder.FindRectangleByPoint(rect, x, y)) {
				index = 1;
			}
			CRect rect1(relation->GetX() + relation->GetWidth() - 10, relation->GetY() + relation->GetHeight() - 10, relation->GetX() + relation->GetWidth() + 10, relation->GetY() + relation->GetHeight() + 10);
			if (finder.FindRectangleByPoint(rect1, x, y)) {
				index = 1;
			}
			if (index == -1) {
				CPoint lineStart(relation->GetX(), relation->GetY());
				while (j < relation->GetLength() && squareFace == false) {
					lineEnd.x = relation->GetAt(j).x;
					lineEnd.y = relation->GetAt(j).y;
					squareFace = finder.FindLineByPoint(lineStart, lineEnd, x, y);
					lineStart.x = lineEnd.x;
					lineStart.y = lineEnd.y;
					j++;
				}
				if (squareFace == false) {
					lineEnd.x = relation->GetWidth() + relation->GetX();
					lineEnd.y = relation->GetHeight() + relation->GetY();
					squareFace = finder.FindLineByPoint(lineStart, lineEnd, x, y);
				}
				if (squareFace == true) {
					index = 2;
				}
			}
		}

		if (dynamic_cast<FigureComposite*>(this->GetAt(i))) {
			composite = static_cast<FigureComposite*>(this->GetAt(i));
			if (dynamic_cast<Class*>(composite)) {
				if (static_cast<Class*>(composite)->GetTempletePosition() != -1) {
					Template *object2 = dynamic_cast<Template*>(composite->GetAt(static_cast<Class*>(composite)->GetTempletePosition()));
					//좌상
					rect.left = composite->GetX() - 3;
					rect.top = object2->GetY() - 3;
					rect.right = composite->GetX() + 6;
					rect.bottom = object2->GetY() + 6;
					ret = finder.FindRectangleByPoint(rect, x, y);
					if (ret != true) {//중 상단
						rect.left = composite->GetX() + (object2->GetX() + object2->GetWidth() - composite->GetX()) / 2 - 4;
						rect.top = object2->GetY() - 3;
						rect.right = composite->GetX() + (object2->GetX() + object2->GetWidth() - composite->GetX()) / 2 + 5;
						rect.bottom = object2->GetY() + 6;

						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					if (ret != true) {//우상
						rect.left = object2->GetX() + object2->GetWidth() - 6;
						rect.top = object2->GetY() - 3;
						rect.right = object2->GetX() + object2->GetWidth() + 3;
						rect.bottom = object2->GetY() + 6;
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					if (ret != true) {//좌중
						rect.left = composite->GetX() - 3;
						rect.top = object2->GetY() + (composite->GetY() + composite->GetHeight() - object2->GetY()) / 2 - 4;;
						rect.right = composite->GetX() + 6;
						rect.bottom = object2->GetY() + (composite->GetY() + composite->GetHeight() - object2->GetY()) / 2 + 5;
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					if (ret != true) {//우중
						rect.left = object2->GetX() + object2->GetWidth() - 6;
						rect.top = object2->GetY() + (composite->GetY() + composite->GetHeight() - object2->GetY()) / 2 - 4;
						rect.right = object2->GetX() + object2->GetWidth() + 3;
						rect.bottom = object2->GetY() + (composite->GetY() + composite->GetHeight() - object2->GetY()) / 2 + 5;
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					if (ret != true) {//좌하
						rect.left = composite->GetX() - 3;
						rect.top = composite->GetY() + composite->GetHeight() - 6;
						rect.right = composite->GetX() + 6;
						rect.bottom = composite->GetY() + composite->GetHeight() + 3;
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					if (ret != true) {//중하
						rect.left = composite->GetX() + (object2->GetX() + object2->GetWidth() - composite->GetX()) / 2 - 4;
						rect.top = composite->GetY() + composite->GetHeight() - 6;
						rect.right = composite->GetX() + (object2->GetX() + object2->GetWidth() - composite->GetX()) / 2 + 5;
						rect.bottom = composite->GetY() + composite->GetHeight() + 3;
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					if (ret != true) {
						rect.left = object2->GetX() + object2->GetWidth() - 6;
						rect.top = composite->GetY() + composite->GetHeight() - 6;
						rect.right = object2->GetX() + object2->GetWidth() + 3;
						rect.bottom = composite->GetY() + composite->GetHeight() + 3;
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
				}
				else {
					rect.left = composite->GetX() - 3;
					rect.top = composite->GetY() - 3;
					rect.right = composite->GetX() + 6;
					rect.bottom = composite->GetY() + 6;
					ret = finder.FindRectangleByPoint(rect, x, y);
					if (ret != true) {//중상
						rect.left = composite->GetX() + composite->GetWidth() / 2 - 4;
						rect.top = composite->GetY() - 3;
						rect.right = composite->GetX() + composite->GetWidth() / 2 + 5;
						rect.bottom = composite->GetY() + 6;
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					if (ret != true) {//
						rect.left = composite->GetX() + composite->GetWidth() - 6;
						rect.top = composite->GetY() - 3;
						rect.right = composite->GetX() + composite->GetWidth() + 3;
						rect.bottom = composite->GetY() + 6;
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					if (ret != true) {
						rect.left = composite->GetX() - 3;
						rect.top = composite->GetY() + composite->GetHeight() / 2 - 4;
						rect.right = composite->GetX() + 6;
						rect.bottom = composite->GetY() + composite->GetHeight() / 2 + 5;
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					if (ret != true) {
						rect.left = composite->GetX() + composite->GetWidth() - 6;
						rect.top = composite->GetY() + composite->GetHeight() / 2 - 4;
						rect.right = composite->GetX() + composite->GetWidth() + 3;
						rect.bottom = composite->GetY() + composite->GetHeight() / 2 + 5;
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					if (ret != true) {
						rect.left = composite->GetX() - 3;
						rect.top = composite->GetY() + composite->GetHeight() - 6;
						rect.right = composite->GetX() + 6;
						rect.bottom = composite->GetY() + composite->GetHeight() + 3;
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					if (ret != true) {
						rect.left = composite->GetX() + composite->GetWidth() / 2 - 4;
						rect.top = composite->GetY() + composite->GetHeight() - 6;
						rect.right = composite->GetX() + composite->GetWidth() / 2 + 5;
						rect.bottom = composite->GetY() + composite->GetHeight() + 3;
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					if (ret != true) {
						rect.left = composite->GetX() + composite->GetWidth() - 6;
						rect.top = composite->GetY() + composite->GetHeight() - 6;
						rect.right = composite->GetX() + composite->GetWidth() + 3;
						rect.bottom = composite->GetY() + composite->GetHeight() + 3;
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
				}
			}
			else {
				rect.left = composite->GetX() - 3;
				rect.top = composite->GetY() - 3;
				rect.right = composite->GetX() + 6;
				rect.bottom = composite->GetY() + 6;
				ret = finder.FindRectangleByPoint(rect, x, y);
				if (ret != true) {
					rect.left = composite->GetX() + composite->GetWidth() / 2 - 4;
					rect.top = composite->GetY() - 3;
					rect.right = composite->GetX() + composite->GetWidth() / 2 + 5;
					rect.bottom = composite->GetY() + 6;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {
					rect.left = composite->GetX() + composite->GetWidth() - 6;
					rect.top = composite->GetY() - 3;
					rect.right = composite->GetX() + composite->GetWidth() + 3;
					rect.bottom = composite->GetY() + 6;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {
					rect.left = composite->GetX() - 3;
					rect.top = composite->GetY() + composite->GetHeight() / 2 - 4;
					rect.right = composite->GetX() + 6;
					rect.bottom = composite->GetY() + composite->GetHeight() / 2 + 5;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {
					rect.left = composite->GetX() + composite->GetWidth() - 6;
					rect.top = composite->GetY() + composite->GetHeight() / 2 - 4;
					rect.right = composite->GetX() + composite->GetWidth() + 3;
					rect.bottom = composite->GetY() + composite->GetHeight() / 2 + 5;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {
					rect.left = composite->GetX() - 3;
					rect.top = composite->GetY() + composite->GetHeight() - 6;
					rect.right = composite->GetX() + 6;
					rect.bottom = composite->GetY() + composite->GetHeight() + 5;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {
					rect.left = composite->GetX() + composite->GetWidth() / 2 - 4;
					rect.top = composite->GetY() + composite->GetHeight() - 6;
					rect.right = composite->GetX() + composite->GetWidth() / 2 + 5;
					rect.bottom = composite->GetY() + composite->GetHeight() + 3;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {
					rect.left = composite->GetX() + composite->GetWidth() - 6;
					rect.top = composite->GetY() + composite->GetHeight() - 6;
					rect.right = composite->GetX() + composite->GetWidth() + 3;
					rect.bottom = composite->GetY() + composite->GetHeight() + 3;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
			}//1여기에 템플릿일때 if() 이거하고/2 템플릿일때 작은 사각형 누르기 하고/3 확대하기 
			CPoint attributeStartPoint(0, 0);
			CPoint attributeEndPoint(0, 0);
			CPoint methodStartPoint(0, 0);
			CPoint methodEndPoint(0, 0);
			CPoint receptionStartPoint(0, 0);
			CPoint receptionEndPoint(0, 0);
			if (dynamic_cast<Class*>(composite)) {
				Class *object = static_cast<Class*>(composite);
				if (object->GetAttributePosition() != -1) {
					attributeStartPoint.x = object->GetAt(object->GetAttributePosition() - 1)->GetX();
					attributeStartPoint.y = object->GetAt(object->GetAttributePosition() - 1)->GetY();
					attributeEndPoint.x = object->GetAt(object->GetAttributePosition() - 1)->GetX() + object->GetAt(object->GetAttributePosition() - 1)->GetWidth();
					attributeEndPoint.y = object->GetAt(object->GetAttributePosition() - 1)->GetY();
				}
				if (object->GetMethodPosition() != -1) {
					methodStartPoint.x = object->GetAt(object->GetMethodPosition() - 1)->GetX();
					methodStartPoint.y = object->GetAt(object->GetMethodPosition() - 1)->GetY();
					methodEndPoint.x = object->GetAt(object->GetMethodPosition() - 1)->GetX() + object->GetAt(object->GetMethodPosition() - 1)->GetWidth();
					methodEndPoint.y = object->GetAt(object->GetMethodPosition() - 1)->GetY();
				}
				if (object->GetReceptionPosition() != -1) {
					receptionStartPoint.x = object->GetAt(object->GetReceptionPosition() - 1)->GetX();
					receptionStartPoint.y = object->GetAt(object->GetReceptionPosition() - 1)->GetY();
					receptionEndPoint.x = object->GetAt(object->GetReceptionPosition() - 1)->GetX() + object->GetAt(object->GetReceptionPosition() - 1)->GetWidth();
					receptionEndPoint.y = object->GetAt(object->GetReceptionPosition() - 1)->GetY();
				}
			}
			if (ret == true) {
				index = 3;
			}
			else {
				rect.left = x - 8;
				rect.top = y - 8;
				rect.right = x + 8;
				rect.bottom = y + 8;
				if (ret != true) {
					ret = finder.FindLineByArea(attributeStartPoint, attributeEndPoint, rect);
				}
				if (ret != true) {
					ret = finder.FindLineByArea(methodStartPoint, methodEndPoint, rect);
				}
				if (ret != true) {
					ret = finder.FindLineByArea(receptionStartPoint, receptionEndPoint, rect);
				}
				if (ret == true) {
					index = 5;
				}
				else {
					if (dynamic_cast<Class*>(composite)) {
						if (static_cast<Class*>(composite)->GetTempletePosition() != -1) {
							Template *object2 = dynamic_cast<Template*>(composite->GetAt(static_cast<Class*>(composite)->GetTempletePosition()));
							rect.left = composite->GetX() - 3;
							rect.top = object2->GetY() - 3;
							rect.right = object2->GetX() + object2->GetWidth() + 3;
							rect.bottom = composite->GetY() + composite->GetHeight() + 3;
						}
						else {
							rect.left = composite->GetX() - 3;
							rect.top = composite->GetY() - 3;
							rect.right = composite->GetX() + composite->GetWidth() + 3;
							rect.bottom = composite->GetY() + composite->GetHeight() + 3;
						}
					}
					else {
						rect.left = composite->GetX() - 3;
						rect.top = composite->GetY() - 3;
						rect.right = composite->GetX() + composite->GetWidth() + 3;
						rect.bottom = composite->GetY() + composite->GetHeight() + 3;
					}

					ret = finder.FindRectangleByPoint(rect, x, y);
					if (ret == true) {
						index = 4;
					}
				}
			}
		}
		i++;
	}
	return index;

}


Long Selection::SelectByPoint(Diagram *diagram, Long x, Long y) {
	Finder finder;
	CRect rect;
	FigureComposite *composite;
	Relation *relation = 0;
	SelfRelation *selfRelation = 0;
	bool ret = false;
	Long i = 0;
	Long j;
	Long k;
	Long index = -1;
	CPoint lineStart;
	CPoint lineEnd;

	while (i < diagram->GetLength() && ret == false) {
		composite = static_cast<FigureComposite*>(diagram->GetAt(i));
		if (dynamic_cast<Class*>(composite)) {
			if (dynamic_cast<Class*>(composite)->GetTempletePosition() != -1) {
				Template *object = dynamic_cast<Template*>(composite->GetAt(static_cast<Class*>(composite)->GetTempletePosition()));
				rect.left = composite->GetX() + 4;
				rect.top = object->GetY() + 4;
				rect.right = object->GetX() + object->GetWidth() - 4;
				rect.bottom = composite->GetY() + composite->GetHeight() - 4;
				ret = finder.FindRectangleByPoint(rect, x, y);
				Template *object2 = dynamic_cast<Template*>(composite->GetAt(static_cast<Class*>(composite)->GetTempletePosition()));
				//좌상
				if (ret != true) {
					rect.left = composite->GetX() - 3;
					rect.top = object2->GetY() - 3;
					rect.right = composite->GetX() + 6;
					rect.bottom = object2->GetY() + 6;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {//중 상단
					rect.left = composite->GetX() + (object2->GetX() + object2->GetWidth() - composite->GetX()) / 2 - 4;
					rect.top = object2->GetY() - 3;
					rect.right = composite->GetX() + (object2->GetX() + object2->GetWidth() - composite->GetX()) / 2 + 5;
					rect.bottom = object2->GetY() + 6;

					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {//우상
					rect.left = object2->GetX() + object2->GetWidth() - 6;
					rect.top = object2->GetY() - 3;
					rect.right = object2->GetX() + object2->GetWidth() + 3;
					rect.bottom = object2->GetY() + 6;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {//좌중
					rect.left = composite->GetX() - 3;
					rect.top = object2->GetY() + (composite->GetY() + composite->GetHeight() - object2->GetY()) / 2 - 4;;
					rect.right = composite->GetX() + 6;
					rect.bottom = object2->GetY() + (composite->GetY() + composite->GetHeight() - object2->GetY()) / 2 + 5;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {//우중
					rect.left = object2->GetX() + object2->GetWidth() - 6;
					rect.top = object2->GetY() + (composite->GetY() + composite->GetHeight() - object2->GetY()) / 2 - 4;
					rect.right = object2->GetX() + object2->GetWidth() + 3;
					rect.bottom = object2->GetY() + (composite->GetY() + composite->GetHeight() - object2->GetY()) / 2 + 5;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {//좌하
					rect.left = composite->GetX() - 3;
					rect.top = composite->GetY() + composite->GetHeight() - 6;
					rect.right = composite->GetX() + 6;
					rect.bottom = composite->GetY() + composite->GetHeight() + 3;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {//중하
					rect.left = composite->GetX() + (object2->GetX() + object2->GetWidth() - composite->GetX()) / 2 - 4;
					rect.top = composite->GetY() + composite->GetHeight() - 6;
					rect.right = composite->GetX() + (object2->GetX() + object2->GetWidth() - composite->GetX()) / 2 + 5;
					rect.bottom = composite->GetY() + composite->GetHeight() + 3;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {
					rect.left = object2->GetX() + object2->GetWidth() - 6;
					rect.top = composite->GetY() + composite->GetHeight() - 6;
					rect.right = object2->GetX() + object2->GetWidth() + 3;
					rect.bottom = composite->GetY() + composite->GetHeight() + 3;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
			}


			else {
				rect.left = composite->GetX() + 4;
				rect.top = composite->GetY() + 4;
				rect.right = composite->GetX() + composite->GetWidth() - 4;
				rect.bottom = composite->GetY() + composite->GetHeight() - 4;
				ret = finder.FindRectangleByPoint(rect, x, y);
				if (ret != true) {
					rect.left = composite->GetX() - 3;
					rect.top = composite->GetY() - 3;
					rect.right = composite->GetX() + 6;
					rect.bottom = composite->GetY() + 6;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {//중상
					rect.left = composite->GetX() + composite->GetWidth() / 2 - 4;
					rect.top = composite->GetY() - 3;
					rect.right = composite->GetX() + composite->GetWidth() / 2 + 5;
					rect.bottom = composite->GetY() + 6;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {//
					rect.left = composite->GetX() + composite->GetWidth() - 6;
					rect.top = composite->GetY() - 3;
					rect.right = composite->GetX() + composite->GetWidth() + 3;
					rect.bottom = composite->GetY() + 6;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {
					rect.left = composite->GetX() - 3;
					rect.top = composite->GetY() + composite->GetHeight() / 2 - 4;
					rect.right = composite->GetX() + 6;
					rect.bottom = composite->GetY() + composite->GetHeight() / 2 + 5;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {
					rect.left = composite->GetX() + composite->GetWidth() - 6;
					rect.top = composite->GetY() + composite->GetHeight() / 2 - 4;
					rect.right = composite->GetX() + composite->GetWidth() + 3;
					rect.bottom = composite->GetY() + composite->GetHeight() / 2 + 5;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {
					rect.left = composite->GetX() - 3;
					rect.top = composite->GetY() + composite->GetHeight() - 6;
					rect.right = composite->GetX() + 6;
					rect.bottom = composite->GetY() + composite->GetHeight() + 3;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {
					rect.left = composite->GetX() + composite->GetWidth() / 2 - 4;
					rect.top = composite->GetY() + composite->GetHeight() - 6;
					rect.right = composite->GetX() + composite->GetWidth() / 2 + 5;
					rect.bottom = composite->GetY() + composite->GetHeight() + 3;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret != true) {
					rect.left = composite->GetX() + composite->GetWidth() - 6;
					rect.top = composite->GetY() + composite->GetHeight() - 6;
					rect.right = composite->GetX() + composite->GetWidth() + 3;
					rect.bottom = composite->GetY() + composite->GetHeight() + 3;
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
			}
		}
		else {
			rect.left = composite->GetX() + 4;
			rect.top = composite->GetY() + 4;
			rect.right = composite->GetX() + composite->GetWidth() - 4;
			rect.bottom = composite->GetY() + composite->GetHeight() - 4;
			ret = finder.FindRectangleByPoint(rect, x, y);
			if (ret != true) {
				rect.left = composite->GetX() - 3;
				rect.top = composite->GetY() - 3;
				rect.right = composite->GetX() + 6;
				rect.bottom = composite->GetY() + 6;
				ret = finder.FindRectangleByPoint(rect, x, y);
			}
			if (ret != true) {//중상
				rect.left = composite->GetX() + composite->GetWidth() / 2 - 4;
				rect.top = composite->GetY() - 3;
				rect.right = composite->GetX() + composite->GetWidth() / 2 + 5;
				rect.bottom = composite->GetY() + 6;
				ret = finder.FindRectangleByPoint(rect, x, y);
			}
			if (ret != true) {//
				rect.left = composite->GetX() + composite->GetWidth() - 6;
				rect.top = composite->GetY() - 3;
				rect.right = composite->GetX() + composite->GetWidth() + 3;
				rect.bottom = composite->GetY() + 6;
				ret = finder.FindRectangleByPoint(rect, x, y);
			}
			if (ret != true) {
				rect.left = composite->GetX() - 3;
				rect.top = composite->GetY() + composite->GetHeight() / 2 - 4;
				rect.right = composite->GetX() + 6;
				rect.bottom = composite->GetY() + composite->GetHeight() / 2 + 5;
				ret = finder.FindRectangleByPoint(rect, x, y);
			}
			if (ret != true) {
				rect.left = composite->GetX() + composite->GetWidth() - 6;
				rect.top = composite->GetY() + composite->GetHeight() / 2 - 4;
				rect.right = composite->GetX() + composite->GetWidth() + 3;
				rect.bottom = composite->GetY() + composite->GetHeight() / 2 + 5;
				ret = finder.FindRectangleByPoint(rect, x, y);
			}
			if (ret != true) {
				rect.left = composite->GetX() - 3;
				rect.top = composite->GetY() + composite->GetHeight() - 6;
				rect.right = composite->GetX() + 6;
				rect.bottom = composite->GetY() + composite->GetHeight() + 3;
				ret = finder.FindRectangleByPoint(rect, x, y);
			}
			if (ret != true) {
				rect.left = composite->GetX() + composite->GetWidth() / 2 - 4;
				rect.top = composite->GetY() + composite->GetHeight() - 6;
				rect.right = composite->GetX() + composite->GetWidth() / 2 + 5;
				rect.bottom = composite->GetY() + composite->GetHeight() + 3;
				ret = finder.FindRectangleByPoint(rect, x, y);
			}
			if (ret != true) {
				rect.left = composite->GetX() + composite->GetWidth() - 6;
				rect.top = composite->GetY() + composite->GetHeight() - 6;
				rect.right = composite->GetX() + composite->GetWidth() + 3;
				rect.bottom = composite->GetY() + composite->GetHeight() + 3;
				ret = finder.FindRectangleByPoint(rect, x, y);
			}
		}
		//1여기에 템플릿일때 if() 이거하고/2 템플릿일때 작은 사각형 누르기 하고/3 확대하기 


		if (ret == true) {
			if (this->length < this->capacity) {
				this->figures.Store(this->length, composite);
			}
			else {
				this->figures.AppendFromRear(composite);
				this->capacity++;
			}
			this->length++;

			index = this->length;
		}

		composite = static_cast<FigureComposite*>(diagram->GetAt(i));
		j = 0;
		while (j < composite->GetLength() && ret == false) {
			if (dynamic_cast<Relation*>(composite->GetAt(j))) {
				relation = static_cast<Relation*>(composite->GetAt(j));


				lineStart.x = relation->GetX();
				lineStart.y = relation->GetY();

				k = 0;
				while (k < relation->GetLength() && ret == false) {

					lineEnd.x = relation->GetAt(k).x;
					lineEnd.y = relation->GetAt(k).y;
					ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
					lineStart.x = lineEnd.x;
					lineStart.y = lineEnd.y;
					k++;
				}

				lineEnd.x = relation->GetWidth() + relation->GetX();
				lineEnd.y = relation->GetHeight() + relation->GetY();
				if (ret == false) {
					ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
				}
				//여기 부터 바깥 사각박스 찾기
				Long l = 0;
				while (l < 5 && ret == false) {
					if (l == 1) {
						rect.left = relation->rollNamePoints->GetAt(l).x - 40;
						rect.right = relation->rollNamePoints->GetAt(l).x + 40;
						rect.top = relation->rollNamePoints->GetAt(l).y - 10;
						rect.bottom = relation->rollNamePoints->GetAt(l).y + 10;
					}
					else if(l == 0|| l == 2){
						rect.left = relation->rollNamePoints->GetAt(l).x - 20;
						rect.right = relation->rollNamePoints->GetAt(l).x + 20;
						rect.top = relation->rollNamePoints->GetAt(l).y - 10;
						rect.bottom = relation->rollNamePoints->GetAt(l).y + 10;
					}
					else if (l == 3||l==4) {
						rect.left = relation->rollNamePoints->GetAt(l).x - 25;
						rect.right = relation->rollNamePoints->GetAt(l).x + 25;
						rect.top = relation->rollNamePoints->GetAt(l).y - 10;
						rect.bottom = relation->rollNamePoints->GetAt(l).y + 10;
					}
					
					if (ret == false) {
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					l++;
				}
				if (ret == true) {
					if (this->length < this->capacity) {
						this->figures.Store(this->length, relation);
					}
					else {
						this->figures.AppendFromRear(relation);
						this->capacity++;
					}
					this->length++;

					index = this->length;
				}
			}
			if (dynamic_cast<SelfRelation*>(composite->GetAt(j))) {
				selfRelation = static_cast<SelfRelation*>(composite->GetAt(j));
				lineStart.x = selfRelation->GetX();
				lineStart.y = selfRelation->GetY();
				lineEnd.x = selfRelation->GetX();
				lineEnd.y = selfRelation->GetY() - 40;
				if (ret == false) {
					ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
				}

				lineStart.x = selfRelation->GetX();
				lineStart.y = selfRelation->GetY() - 40;
				lineEnd.x = selfRelation->GetX() + 80;
				lineEnd.y = selfRelation->GetY() - 40;
				if (ret == false) {
					ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
				}

				lineStart.x = selfRelation->GetX() + 80;
				lineStart.y = selfRelation->GetY() - 40;
				lineEnd.x = selfRelation->GetX() + 80;
				lineEnd.y = selfRelation->GetY() + 40;
				if (ret == false) {
					ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
				}

				lineStart.x = selfRelation->GetX() + 80;
				lineStart.y = selfRelation->GetY() + 40;
				lineEnd.x = selfRelation->GetX() + 30;
				lineEnd.y = selfRelation->GetY() + 40;
				if (ret == false) {
					ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
				}
				//여기 부터 바깥 사각박스 찾기
				rect.left = selfRelation->rollNamePoints->GetAt(0).x - 10;
				rect.right = selfRelation->rollNamePoints->GetAt(0).x + 20;
				rect.top = selfRelation->rollNamePoints->GetAt(0).y - 10;
				rect.bottom = selfRelation->rollNamePoints->GetAt(0).y + 10;
				if (ret == false) {
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				rect.left = selfRelation->rollNamePoints->GetAt(1).x - 30;
				rect.right = selfRelation->rollNamePoints->GetAt(1).x + 30;
				rect.top = selfRelation->rollNamePoints->GetAt(1).y - 10;
				rect.bottom = selfRelation->rollNamePoints->GetAt(1).y + 10;
				if (ret == false) {
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				rect.left = selfRelation->rollNamePoints->GetAt(2).x - 20;
				rect.right = selfRelation->rollNamePoints->GetAt(2).x + 50;
				rect.top = selfRelation->rollNamePoints->GetAt(2).y - 10;
				rect.bottom = selfRelation->rollNamePoints->GetAt(2).y + 10;
				if (ret == false) {
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				rect.left = selfRelation->rollNamePoints->GetAt(3).x - 20;
				rect.right = selfRelation->rollNamePoints->GetAt(3).x + 50;
				rect.top = selfRelation->rollNamePoints->GetAt(3).y - 10;
				rect.bottom = selfRelation->rollNamePoints->GetAt(3).y + 10;
				if (ret == false) {
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				rect.left = selfRelation->rollNamePoints->GetAt(4).x - 20;
				rect.right = selfRelation->rollNamePoints->GetAt(4).x + 10;
				rect.top = selfRelation->rollNamePoints->GetAt(4).y - 10;
				rect.bottom = selfRelation->rollNamePoints->GetAt(4).y + 10;
				if (ret == false) {
					ret = finder.FindRectangleByPoint(rect, x, y);
				}
				if (ret == true) {
					if (this->length < this->capacity) {
						this->figures.Store(this->length, selfRelation);
					}
					else {
						this->figures.AppendFromRear(selfRelation);
						this->capacity++;
					}
					this->length++;

					index = this->length;
				}
			}
			j++;
		}
		i++;
	}
	return index;
}

void Selection::Accept(Diagram *diagram, Visitor& visitor, Long distanceX, Long distanceY) {
	visitor.Visit(diagram, this, distanceX, distanceY);
}

void Selection::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}

Long Selection::Correct(Figure *figure, Long index) {
	index = this->figures.Modify(index, figure);
	return index;
}
Long Selection::SelectByPointForRelation(Diagram *diagram, Long x, Long y) {
	Finder finder;
	CRect rect;
	FigureComposite *composite;
	
	bool ret = false;
	Long i = 0;
	Long index = -1;


	while (i < diagram->GetLength() && ret == false) {
		composite = static_cast<FigureComposite*>(diagram->GetAt(i));
		if (dynamic_cast<Class*>(composite)) {
			if (dynamic_cast<Class*>(composite)->GetTempletePosition() != -1) {
				Template *object = dynamic_cast<Template*>(composite->GetAt(static_cast<Class*>(composite)->GetTempletePosition()));
				rect.left = composite->GetX();
				rect.top = object->GetY();
				rect.right = object->GetX() + object->GetWidth();
				rect.bottom = composite->GetY() + composite->GetHeight();
				ret = finder.FindRectangleByPoint(rect, x, y);

			}


			else {
				rect.left = composite->GetX();
				rect.top = composite->GetY();
				rect.right = composite->GetX() + composite->GetWidth();
				rect.bottom = composite->GetY() + composite->GetHeight();
				ret = finder.FindRectangleByPoint(rect, x, y);

			}
		}


		//1여기에 템플릿일때 if() 이거하고/2 템플릿일때 작은 사각형 누르기 하고/3 확대하기 


		if (ret == true) {
			if (this->length < this->capacity) {
				this->figures.Store(this->length, composite);
			}
			else {
				this->figures.AppendFromRear(composite);
				this->capacity++;
			}
			this->length++;

			index = this->length;
		}
		i++;
	}
	return index;
}