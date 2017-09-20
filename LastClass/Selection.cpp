#include  "Selection.h"
#include "Diagram.h"
#include "Relation.h"
#include "FigureComposite.h"
#include "Finder.h"
#include "SelfRelation.h"
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

	if (this->figures[index] != 0) {
		delete this->figures[index];
	}
	this->length--;
	this->capacity--;
	return this->figures.Delete(index);

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
		index = this->figures.Delete(0);
		this->length--;
		this->capacity--;
	}
	i = 0;
	Long j ;

	while (i < diagram->GetLength() && index == -1) {
		j = 0;
		figures =static_cast<FigureComposite*>(diagram->GetAt(i));
		while (j < figures->GetLength() && figure != figures->GetAt(j)) {
			j++;
		}
		if (j < figures->GetLength()) {
			index = j;
			figures->Remove(index);
			index = this->figures.Delete(0);
			this->length--;
			this->capacity--;
		}
		i++;
	}
	
	return index;
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
				lineEnd.y= selfRelation->GetY() - 30;
				if (ret == false) {
					ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
				}
				
				lineStart.x = selfRelation->GetX();
				lineStart.y = selfRelation->GetY() - 30;
				lineEnd.x = selfRelation->GetX() + 60;
				lineEnd.y = selfRelation->GetY() - 30;
				if (ret == false) {
					ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
				}
		
				lineStart.x = selfRelation->GetX() + 60;
				lineStart.y = selfRelation->GetY() - 30;
				lineEnd.x = selfRelation->GetX() + 60;
				lineEnd.y = selfRelation->GetY() + 30;
				if (ret == false) {
					ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
				}
			
				lineStart.x = selfRelation->GetX() + 60;
				lineStart.y = selfRelation->GetY() + 30;
				lineEnd.x = selfRelation->GetX() + 30;
				lineEnd.y = selfRelation->GetY() + 30;
				if (ret == false) {
					ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
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

void Selection :: Accept(Diagram *diagram,Visitor& visitor, Long distanceX, Long distanceY) {
	visitor.Visit(diagram,this, distanceX,distanceY);
}

void Selection::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);
}
