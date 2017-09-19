#include  "Selection.h"
#include "Diagram.h"
#include "Relation.h"
#include "Finder.h"

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
	
	while (this->length != 0){
		this->figures.Modify(this->length -1 , 0);
		this->length--;
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
		//¼öÁ¤
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
			
Long Selection::SelectByPoint(Diagram *diagram, Long x, Long y) {
	Finder finder;
	CRect rect;
	FigureComposite *composite;
	Relation *relation=0;
	bool ret = false;
	Long i = 0;
	Long j;
	Long k;
	Long index = -1;

	while (i < diagram->GetLength() && ret == false) {
		
		composite = static_cast<FigureComposite*>(diagram->GetAt(i));
		rect.left = composite->GetX();
		rect.top = composite->GetY();
		rect.right = composite->GetX() + composite->GetWidth();
		rect.bottom = composite->GetY() + composite->GetHeight();

		ret = finder.FindRectangleByPoint(rect, x, y);

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

				CPoint lineStart(relation->GetX(), relation->GetY());
				CPoint lineEnd;

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
			j++;
		}
		i++;
	}
	return index;
}

void Selection :: Accept(Visitor& visitor, Long distanceX, Long distanceY) {
	visitor.Visit(this, distanceX,distanceY);
}

void Selection::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);
}
