//Class.cpp

#include "Class.h"
#include "Line.h"
#include "Generalization.h"
#include "Realization.h"
#include "Dependency.h"
#include "Association.h"
#include "DirectedAssociation.h"
#include "Aggregation.h"
#include "Aggregations.h"
#include "Composition.h"
#include "Compositions.h"
#include "Template.h"
#include "SmartPointer.h"
#include "MemoLine.h"
#include "SelfGeneralization.h"
#include "SelfDependency.h"
#include "SelfAggregation.h"
#include "SelfAssociation.h"
#include "SelfAggregations.h"
#include "SelfDirectedAssociation.h"
#include "SelfComposition.h"
#include "SelfCompositions.h"
#include "SmartPointer.h"
#include "ArrayIterator.h"
#include "Reception.h"
#include "Iterator.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "Reception.h"
#include "Diagram.h"
#include "Finder.h"

#include "RollNameBox.h"

Class::Class(Long capacity) :FigureComposite(capacity) {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->attributePosition = -1;
	this->methodPosition = -1;
	this->receptionPosition = -1;
	this->templetePosition = -1;
}
Class::Class(Long x, Long y, Long width, Long height) : FigureComposite(64) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->attributePosition = -1;
	this->methodPosition = -1;
	this->receptionPosition = -1;
	this->templetePosition = -1;
}

Class::Class(const Class& source) : FigureComposite(source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->attributePosition = source.attributePosition;
	this->methodPosition = source.methodPosition;
	this->receptionPosition = source.receptionPosition;
	this->templetePosition = source.templetePosition;
}

Class::~Class() {
	Long i = 0;
	while (i < this->length) {
		delete this->figures[i];
		i++;
	}
}
void Class::Initialize() {
	ClassName className(this->x, this->y, this->width, 50, "");
	this->figures.Store(this->length, className.Clone());
	this->length++;

	Line line1(this->x, this->y + 50, width, 0);
	this->figures.Store(this->length, line1.Clone());
	this->length++;

	Attribute attribute(this->x, this->y + 50, this->width, ((this->y + 50 + this->y + this->height) / 2) - (this->y + 50), "");
	this->attributePosition = this->figures.Store(this->length, attribute.Clone());
	this->length++;

	Line line2(this->x, (this->y + 50 + this->y + this->height) / 2, this->width, 0);
	this->figures.Store(this->length, line2.Clone());
	this->length++;

	Method method(this->x, (this->y + 50 + this->y + this->height) / 2, this->width, ((this->y + 50 + this->y + this->height) / 2) - (this->y + 50), "");
	this->methodPosition = this->figures.Store(this->length, method.Clone());
	this->length++;

}
Figure* Class::Move(Long distanceX, Long distanceY) {
	Figure::Move(distanceX, distanceY);
	return this;
}
Class& Class::operator = (const Class& source) {
	this->figures = source.figures;
	Long i = 0;
	while (i < source.length) {
		this->figures.Modify(i, (const_cast<Class&>(source)).figures[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->attributePosition = source.attributePosition;
	this->methodPosition = source.methodPosition;
	this->receptionPosition = source.receptionPosition;
	this->templetePosition = source.templetePosition;

	return *this;
}

Figure* Class::operator [] (Long index) {
	return this->figures[index];
}

Long Class::Add(Figure *figure) {
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
Long Class::Add(Attribute *attribute) {
	if (this->length < this->capacity) {
		this->attributePosition= this->figures.Store(this->length, attribute);
	}
	else {
		this->attributePosition = this->figures.AppendFromRear(attribute);
		this->capacity++;
	}
	this->length++;
	return this->attributePosition;
}
Long Class::Add(Method *method) {
	if (this->length < this->capacity) {
		this->methodPosition = this->figures.Store(this->length, method);
	}
	else {
		this->methodPosition = this->figures.AppendFromRear(method);
		this->capacity++;
	}
	this->length++;
	return this->methodPosition;
}
Long Class::Add(Reception *reception) {
	if (this->length < this->capacity) {
		this->receptionPosition = this->figures.Store(this->length, reception);
	}
	else {
		this->receptionPosition = this->figures.AppendFromRear(reception);
		this->capacity++;
	}
	this->length++;
	return this->receptionPosition;
}
Long Class::Add(Template *object) {
	if (this->length < this->capacity) {
		this->templetePosition = this->figures.Store(this->length, object);
	}
	else {
		this->templetePosition = this->figures.AppendFromRear(object);
		this->capacity++;
	}
	this->length++;
	return this->templetePosition;
}
Long Class::Add(Long x, Long y, Long width, Long height) {
	Long index;
	Line object(x, y, width, height);

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



Long Class::AddGeneralization(Long x, Long y, Long width, Long height) {
	Long index;
	Generalization object(x, y, width, height);

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

Long Class::AddRealization(Long x, Long y, Long width, Long height) {
	Long index;
	Realization object(x, y, width, height);

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

Long Class::AddDependency(Long x, Long y, Long width, Long height) {
	Long index;
	Dependency object(x, y, width, height);

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

Long Class::AddAssociation(Long x, Long y, Long width, Long height) {
	Long index;
	Association object(x, y, width, height);

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

Long Class::AddDirectedAssociation(Long x, Long y, Long width, Long height) {
	Long index;
	DirectedAssociation object(x, y, width, height);

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

Long Class::AddAggregation(Long x, Long y, Long width, Long height) {
	Long index;
	Aggregation object(x, y, width, height);

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

Long Class::AddAggregations(Long x, Long y, Long width, Long height) {
	Long index;
	Aggregations object(x, y, width, height);

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

Long Class::AddComposition(Long x, Long y, Long width, Long height) {
	Long index;
	Composition object(x, y, width, height);

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
Long Class::AddCompositions(Long x, Long y, Long width, Long height) {
	Long index;
	Compositions object(x, y, width, height);

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
Long Class::AddAttribute(Diagram *diagram) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	Line line(this->x, this->y + this->figures.GetAt(0)->GetHeight(), this->width, 0);
	if (this->length < this->capacity) {
		this->figures.Store(this->length, line.Clone());
	}
	else {
		this->figures.AppendFromRear(line.Clone());
		this->capacity++;
	}
	this->length++;
	Attribute object(this->x, this->y + this->figures.GetAt(0)->GetHeight(), this->width, 50, "");
	if (this->length < this->capacity) {
		this->attributePosition = this->figures.Store(this->length, object.Clone());
	}
	else {
		this->attributePosition = this->figures.AppendFromRear(object.Clone());
		this->capacity++;
	}
	this->length++;

	this->height += 50;
	if (this->methodPosition != -1) {
		this->figures.GetAt(this->methodPosition)->Move(0, 50);
		this->figures.GetAt(this->methodPosition - 1)->Move(0, 50);
	}
	if (this->receptionPosition != -1) {
		this->figures.GetAt(this->receptionPosition)->Move(0, 50);
		this->figures.GetAt(this->receptionPosition - 1)->Move(0, 50);
	}

	Long i = 0;
	Long j = 0;
	Long Quadrant;
	Finder finder;
	while (i < this->GetLength()) {

		if (dynamic_cast<Relation*>(this->GetAt(i))) {
			Quadrant = finder.FindQuadrant(this->GetAt(i)->GetX(), this->GetAt(i)->GetY(),
				this->GetX(), this->GetY(), this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight() - 50);
			if (Quadrant == 3) {
				this->GetAt(i)->Modify(this->GetAt(i)->GetX(), this->GetAt(i)->GetY() + 50, this->GetAt(i)->GetWidth(), this->GetAt(i)->GetHeight() - 50);
			}
			Relation *relation = static_cast<Relation*>(this->GetAt(i));
			if (relation->GetLength() == 0) {
				CPoint startPoint{ relation->GetX(), relation->GetY() };
				CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
				cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
				cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
				cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
				cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
				cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
				relation->rollNamePoints->Modify(0, cPoint1);
				relation->rollNamePoints->Modify(1, cPoint2);
				relation->rollNamePoints->Modify(2, cPoint3);
				relation->rollNamePoints->Modify(3, cPoint4);
				relation->rollNamePoints->Modify(4, cPoint5);
			}
			else {
				CPoint startPoint{ relation->GetX(), relation->GetY() };
				CPoint endPoint{ relation->GetAt(0).x, relation->GetAt(0).y };
				cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
				cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
				relation->rollNamePoints->Modify(0, cPoint1);
				relation->rollNamePoints->Modify(3, cPoint4);

				CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
					relation->GetAt(relation->GetLength() - 1).y };
				CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
				cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
				cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
				relation->rollNamePoints->Modify(2, cPoint3);
				relation->rollNamePoints->Modify(4, cPoint5);

				if (relation->GetLength() % 2 == 0) {//¦��

					CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
						relation->GetAt((relation->GetLength() - 1) / 2).y };
					CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
						relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
					cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
					relation->rollNamePoints->Modify(1, cPoint2);

				}
				else {//Ȧ��

					CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
						relation->GetAt((relation->GetLength() - 1) / 2).y };
					cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
					relation->rollNamePoints->Modify(1, cPoint2);

				}
			}
		}
		i++;
	}
	i = 0;
	Long startX = this->GetX();
	Long startY = this->GetY();
	Long endX = this->GetX() + this->GetWidth();
	Long endY = this->GetY() + this->GetHeight();
	while (i<diagram->GetLength()) {
		j = 0;
		FigureComposite *figureComposite = dynamic_cast<FigureComposite*>(diagram->GetAt(i));
		while (j < figureComposite->GetLength()) {
			Figure *figure = figureComposite->GetAt(j);
			if (dynamic_cast<Relation*>(figureComposite->GetAt(j))) {
				Relation *relation = static_cast<Relation*>(figureComposite->GetAt(j));
				Long relationEndX = figure->GetX() + figure->GetWidth();
				Long relationEndY = figure->GetY() + figure->GetHeight();
				if (startX <= relationEndX &&  relationEndX <= endX &&
					startY <= relationEndY &&  relationEndY <= endY) {
					Quadrant = finder.FindQuadrant(relationEndX, relationEndY,
						startX, startY, endX, endY - 50);
					if (Quadrant == 3) {
						figure->EndPointMove(0, 50);
					}
					if (relation->GetLength() == 0) {
						CPoint startPoint{ relation->GetX(), relation->GetY() };
						CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
						cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
						cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
						cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
						cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
						cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
						relation->rollNamePoints->Modify(0, cPoint1);
						relation->rollNamePoints->Modify(1, cPoint2);
						relation->rollNamePoints->Modify(2, cPoint3);
						relation->rollNamePoints->Modify(3, cPoint4);
						relation->rollNamePoints->Modify(4, cPoint5);
					}
					else {
						CPoint startPoint{ relation->GetX(), relation->GetY() };
						CPoint endPoint{ relation->GetAt(0).x, relation->GetAt(0).y };
						cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
						cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
						relation->rollNamePoints->Modify(0, cPoint1);
						relation->rollNamePoints->Modify(3, cPoint4);

						CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
							relation->GetAt(relation->GetLength() - 1).y };
						CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
						cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
						cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
						relation->rollNamePoints->Modify(2, cPoint3);
						relation->rollNamePoints->Modify(4, cPoint5);

						if (relation->GetLength() % 2 == 0) {//¦��

							CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
								relation->GetAt((relation->GetLength() - 1) / 2).y };
							CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
								relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
							cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
							relation->rollNamePoints->Modify(1, cPoint2);

						}
						else {//Ȧ��

							CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
								relation->GetAt((relation->GetLength() - 1) / 2).y };
							cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
							relation->rollNamePoints->Modify(1, cPoint2);

						}
					}
				}
			}
			j++;
		}
		i++;
	}
	return this->attributePosition;
}
Long Class::AddMethod(Diagram *diagram) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	Long y;

	if (this->attributePosition == -1) {
		y = this->y + this->figures.GetAt(0)->GetHeight();
	}
	else {
		y = this->figures.GetAt(this->attributePosition)->GetY() + this->figures.GetAt(this->attributePosition)->GetHeight();

	}
	Line line(this->x, y, this->width, 0);
	if (this->length < this->capacity) {
		this->figures.Store(this->length, line.Clone());
	}
	else {
		this->figures.AppendFromRear(line.Clone());
		this->capacity++;
	}
	this->length++;
	Method object(this->x, y, this->width, 100, "");
	if (this->length < this->capacity) {
		this->methodPosition = this->figures.Store(this->length, object.Clone());
	}
	else {
		this->methodPosition = this->figures.AppendFromRear(object.Clone());
		this->capacity++;
	}
	this->length++;

	this->height += 100;

	if (this->receptionPosition != -1) {
		this->figures.GetAt(this->receptionPosition)->Move(0, 100);
		this->figures.GetAt(this->receptionPosition - 1)->Move(0, 100);
	}

	Long i = 0;
	Long j = 0;
	Long Quadrant;
	Finder finder;
	while (i < this->GetLength()) {

		if (dynamic_cast<Relation*>(this->GetAt(i))) {
			Quadrant = finder.FindQuadrant(this->GetAt(i)->GetX(), this->GetAt(i)->GetY(),
				this->GetX(), this->GetY(), this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight() - 100);
			if (Quadrant == 3) {
				this->GetAt(i)->Modify(this->GetAt(i)->GetX(), this->GetAt(i)->GetY() + 100, this->GetAt(i)->GetWidth(), this->GetAt(i)->GetHeight() - 100);
			}
			Relation *relation = static_cast<Relation*>(this->GetAt(i));
			if (relation->GetLength() == 0) {
				CPoint startPoint{ relation->GetX(), relation->GetY() };
				CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
				cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
				cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
				cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
				cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
				cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
				relation->rollNamePoints->Modify(0, cPoint1);
				relation->rollNamePoints->Modify(1, cPoint2);
				relation->rollNamePoints->Modify(2, cPoint3);
				relation->rollNamePoints->Modify(3, cPoint4);
				relation->rollNamePoints->Modify(4, cPoint5);
			}
			else {
				CPoint startPoint{ relation->GetX(), relation->GetY() };
				CPoint endPoint{ relation->GetAt(0).x, relation->GetAt(0).y };
				cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
				cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
				relation->rollNamePoints->Modify(0, cPoint1);
				relation->rollNamePoints->Modify(3, cPoint4);

				CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
					relation->GetAt(relation->GetLength() - 1).y };
				CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
				cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
				cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
				relation->rollNamePoints->Modify(2, cPoint3);
				relation->rollNamePoints->Modify(4, cPoint5);

				if (relation->GetLength() % 2 == 0) {//¦��

					CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
						relation->GetAt((relation->GetLength() - 1) / 2).y };
					CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
						relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
					cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
					relation->rollNamePoints->Modify(1, cPoint2);

				}
				else {//Ȧ��

					CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
						relation->GetAt((relation->GetLength() - 1) / 2).y };
					cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
					relation->rollNamePoints->Modify(1, cPoint2);

				}
			}
		}
		i++;
	}
	i = 0;
	Long startX = this->GetX();
	Long startY = this->GetY();
	Long endX = this->GetX() + this->GetWidth();
	Long endY = this->GetY() + this->GetHeight();
	while (i<diagram->GetLength()) {
		j = 0;
		FigureComposite *figureComposite = dynamic_cast<FigureComposite*>(diagram->GetAt(i));
		while (j < figureComposite->GetLength()) {
			Figure *figure = figureComposite->GetAt(j);
			if (dynamic_cast<Relation*>(figureComposite->GetAt(j))) {
				Relation *relation = static_cast<Relation*>(figureComposite->GetAt(j));
				Long relationEndX = figure->GetX() + figure->GetWidth();
				Long relationEndY = figure->GetY() + figure->GetHeight();
				if (startX <= relationEndX &&  relationEndX <= endX &&
					startY <= relationEndY &&  relationEndY <= endY) {
					Quadrant = finder.FindQuadrant(relationEndX, relationEndY,
						startX, startY, endX, endY - 100);
					if (Quadrant == 3) {
						figure->EndPointMove(0, 100);
					}

					if (relation->GetLength() == 0) {
						CPoint startPoint{ relation->GetX(), relation->GetY() };
						CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
						cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
						cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
						cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
						cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
						cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
						relation->rollNamePoints->Modify(0, cPoint1);
						relation->rollNamePoints->Modify(1, cPoint2);
						relation->rollNamePoints->Modify(2, cPoint3);
						relation->rollNamePoints->Modify(3, cPoint4);
						relation->rollNamePoints->Modify(4, cPoint5);
					}
					else {
						CPoint startPoint{ relation->GetX(), relation->GetY() };
						CPoint endPoint{ relation->GetAt(0).x, relation->GetAt(0).y };
						cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
						cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
						relation->rollNamePoints->Modify(0, cPoint1);
						relation->rollNamePoints->Modify(3, cPoint4);

						CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
							relation->GetAt(relation->GetLength() - 1).y };
						CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
						cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
						cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
						relation->rollNamePoints->Modify(2, cPoint3);
						relation->rollNamePoints->Modify(4, cPoint5);

						if (relation->GetLength() % 2 == 0) {//¦��

							CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
								relation->GetAt((relation->GetLength() - 1) / 2).y };
							CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
								relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
							cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
							relation->rollNamePoints->Modify(1, cPoint2);

						}
						else {//Ȧ��

							CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
								relation->GetAt((relation->GetLength() - 1) / 2).y };
							cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
							relation->rollNamePoints->Modify(1, cPoint2);

						}
					}
				}
			}
			j++;
		}
		i++;
	}
	return this->methodPosition;
}
Long Class::AddReception(Diagram *diagram) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	Line line(this->x, this->y + this->height, this->width, 0);


	if (this->length < this->capacity) {
		this->figures.Store(this->length, line.Clone());
	}
	else {
		this->figures.AppendFromRear(line.Clone());
		this->capacity++;
	}
	this->length++;

	Reception reception(this->x, this->y + this->height, this->width, 50, "");

	if (this->length < this->capacity) {
		this->receptionPosition = this->figures.Store(this->length, reception.Clone());
	}
	else {
		this->receptionPosition = this->figures.AppendFromRear(reception.Clone());
		this->capacity++;
	}
	this->length++;
	this->height = height + 50;
	Long i = 0;
	Long j = 0;
	Finder finder;
	Long Quadrant;
	while (i < this->GetLength()) {
		if (dynamic_cast<Relation*>(this->GetAt(i))) {
			Quadrant = finder.FindQuadrant(this->GetAt(i)->GetX(), this->GetAt(i)->GetY(),
				this->GetX(), this->GetY(), this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight() - 50);
			if (Quadrant == 3) {
				this->GetAt(i)->Modify(this->GetAt(i)->GetX(), this->GetAt(i)->GetY() + 50, this->GetAt(i)->GetWidth(), this->GetAt(i)->GetHeight() - 50);
			}
			Relation *relation = static_cast<Relation*>(this->GetAt(i));
			if (relation->GetLength() == 0) {
				CPoint startPoint{ relation->GetX(), relation->GetY() };
				CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
				cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
				cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
				cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
				cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
				cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
				relation->rollNamePoints->Modify(0, cPoint1);
				relation->rollNamePoints->Modify(1, cPoint2);
				relation->rollNamePoints->Modify(2, cPoint3);
				relation->rollNamePoints->Modify(3, cPoint4);
				relation->rollNamePoints->Modify(4, cPoint5);
			}
			else {
				CPoint startPoint{ relation->GetX(), relation->GetY() };
				CPoint endPoint{ relation->GetAt(0).x, relation->GetAt(0).y };
				cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
				cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
				relation->rollNamePoints->Modify(0, cPoint1);
				relation->rollNamePoints->Modify(3, cPoint4);

				CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
					relation->GetAt(relation->GetLength() - 1).y };
				CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
				cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
				cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
				relation->rollNamePoints->Modify(2, cPoint3);
				relation->rollNamePoints->Modify(4, cPoint5);

				if (relation->GetLength() % 2 == 0) {//¦��

					CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
						relation->GetAt((relation->GetLength() - 1) / 2).y };
					CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
						relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
					cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
					relation->rollNamePoints->Modify(1, cPoint2);

				}
				else {//Ȧ��

					CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
						relation->GetAt((relation->GetLength() - 1) / 2).y };
					cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
					relation->rollNamePoints->Modify(1, cPoint2);

				}
			}
		}
		i++;
	}
	i = 0;
	Long startX = this->GetX();
	Long startY = this->GetY();
	Long endX = this->GetX() + this->GetWidth();
	Long endY = this->GetY() + this->GetHeight();
	while (i<diagram->GetLength()) {
		j = 0;
		FigureComposite *figureComposite = dynamic_cast<FigureComposite*>(diagram->GetAt(i));
		while (j < figureComposite->GetLength()) {
			Figure *figure = figureComposite->GetAt(j);
			if (dynamic_cast<Relation*>(figureComposite->GetAt(j))) {
				Long relationEndX = figure->GetX() + figure->GetWidth();
				Long relationEndY = figure->GetY() + figure->GetHeight();
				if (startX <= relationEndX &&  relationEndX <= endX &&
					startY <= relationEndY &&  relationEndY <= endY) {
					Quadrant = finder.FindQuadrant(relationEndX, relationEndY,
						startX, startY, endX, endY - 50);
					if (Quadrant == 3) {
						figure->EndPointMove(0, 50);
					}
					Relation *relation = static_cast<Relation*>(figureComposite->GetAt(j));
					if (relation->GetLength() == 0) {
						CPoint startPoint{ relation->GetX(), relation->GetY() };
						CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
						cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
						cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
						cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
						cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
						cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
						relation->rollNamePoints->Modify(0, cPoint1);
						relation->rollNamePoints->Modify(1, cPoint2);
						relation->rollNamePoints->Modify(2, cPoint3);
						relation->rollNamePoints->Modify(3, cPoint4);
						relation->rollNamePoints->Modify(4, cPoint5);
					}
					else {
						CPoint startPoint{ relation->GetX(), relation->GetY() };
						CPoint endPoint{ relation->GetAt(0).x, relation->GetAt(0).y };
						cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
						cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
						relation->rollNamePoints->Modify(0, cPoint1);
						relation->rollNamePoints->Modify(3, cPoint4);

						CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
							relation->GetAt(relation->GetLength() - 1).y };
						CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
						cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
						cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
						relation->rollNamePoints->Modify(2, cPoint3);
						relation->rollNamePoints->Modify(4, cPoint5);

						if (relation->GetLength() % 2 == 0) {//¦��

							CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
								relation->GetAt((relation->GetLength() - 1) / 2).y };
							CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
								relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
							cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
							relation->rollNamePoints->Modify(1, cPoint2);

						}
						else {//Ȧ��

							CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
								relation->GetAt((relation->GetLength() - 1) / 2).y };
							cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
							relation->rollNamePoints->Modify(1, cPoint2);

						}
					}
				}
			}
			j++;
		}
		i++;
	}

	return this->receptionPosition;
}


Long Class::AddTemplate(Long x, Long y, Long width, Long height) {

	Template object(x, y, width, height);

	if (this->length < this->capacity) {
		this->templetePosition = this->figures.Store(this->length, object.Clone());
	}
	else {
		this->templetePosition = this->figures.AppendFromRear(object.Clone());
		this->capacity++;
	}
	this->length++;

	return this->templetePosition;
}

Long Class::Remove(Long index) {

	if (this->figures[index] != 0) {
		delete this->figures[index];
	}
	this->length--;
	this->capacity--;
	return this->figures.Delete(index);
}
Long Class::RemoveAttribute() {

	if (this->attributePosition != -1) {
		this->figures.GetAt(0)->Modify(this->x, this->y, this->width, this->figures.GetAt(0)->GetHeight() + this->figures.GetAt(this->attributePosition)->GetHeight());
		if (this->attributePosition < this->methodPosition) {
			this->methodPosition -= 2;
		}
		if (this->attributePosition < this->receptionPosition) {
			this->receptionPosition -= 2;
		}
		if (this->attributePosition < this->templetePosition) {
			this->templetePosition -= 2;
		}

		delete this->figures.GetAt(this->attributePosition);
		this->figures.Delete(this->attributePosition);
		this->length--;
		this->capacity--;

		delete this->figures.GetAt(this->attributePosition - 1);
		this->attributePosition = this->figures.Delete(this->attributePosition - 1);
		this->length--;
		this->capacity--;
	}

	return this->attributePosition;
}
Long Class::RemoveMethod() {
	if (this->methodPosition != -1) {
		if (this->attributePosition == -1) {
			this->figures.GetAt(0)->Modify(this->x, this->y, this->width, this->figures.GetAt(0)->GetHeight() + this->figures.GetAt(this->methodPosition)->GetHeight());
		}
		else {
			this->figures.GetAt(this->attributePosition)->Modify(this->x, this->figures.GetAt(this->attributePosition)->GetY(), this->width, this->figures.GetAt(this->attributePosition)->GetHeight() + this->figures.GetAt(this->methodPosition)->GetHeight());
		}
		if (this->methodPosition < this->attributePosition) {
			this->attributePosition -= 2;
		}
		if (this->methodPosition < this->receptionPosition) {
			this->receptionPosition -= 2;
		}
		if (this->methodPosition < this->templetePosition) {
			this->templetePosition -= 2;
		}
		delete this->figures.GetAt(this->methodPosition);
		this->figures.Delete(this->methodPosition);
		this->length--;
		this->capacity--;

		delete this->figures.GetAt(this->methodPosition - 1);
		this->methodPosition = this->figures.Delete(this->methodPosition - 1);
		this->length--;
		this->capacity--;
	}
	return this->methodPosition;
}
Long Class::RemoveReception() {
	if (this->receptionPosition != -1) {
		if (this->methodPosition != -1) {
		this->figures.GetAt(this->methodPosition)->Modify(this->x, this->figures.GetAt(this->methodPosition)->GetY(), this->width, this->figures.GetAt(this->methodPosition)->GetHeight() + this->figures.GetAt(this->receptionPosition)->GetHeight());
		}
		else if (this->attributePosition != -1) {
			this->figures.GetAt(this->attributePosition)->Modify(this->x, this->figures.GetAt(this->attributePosition)->GetY(), this->width, this->figures.GetAt(attributePosition)->GetHeight() + this->figures.GetAt(this->receptionPosition)->GetHeight());
		}
		else {
			this->figures.GetAt(0)->Modify(this->x, this->y, this->width, this->figures.GetAt(0)->GetHeight() + this->figures.GetAt(this->receptionPosition)->GetHeight());
		}
		if (this->receptionPosition < this->attributePosition) {
			this->attributePosition -= 2;
		}
		if (this->receptionPosition < this->methodPosition) {
			this->methodPosition -= 2;
		}
		if (this->receptionPosition < this->templetePosition) {
			this->templetePosition -= 2;
		}
		delete this->figures.GetAt(this->receptionPosition);
		this->figures.Delete(this->receptionPosition);
		this->length--;
		this->capacity--;

		delete this->figures.GetAt(this->receptionPosition - 1);
		this->receptionPosition = this->figures.Delete(this->receptionPosition - 1);
		this->length--;
		this->capacity--;
	}
	return this->receptionPosition;
}
Long Class::RemoveTemplate() {
	if (this->templetePosition != -1) {

		if (this->templetePosition < this->attributePosition) {
			this->attributePosition--;
		}
		if (this->templetePosition < this->methodPosition) {
			this->methodPosition--;
		}
		if (this->templetePosition < this->receptionPosition) {
			this->receptionPosition--;
		}
		delete this->figures.GetAt(this->templetePosition);
		this->templetePosition = this->figures.Delete(this->templetePosition);
		this->length--;
		this->capacity--;
	}
	return this->templetePosition;
}

Figure* Class::GetAt(Long index) {
	return static_cast<Figure*>(this->figures.GetAt(index));
}

Figure* Class::Clone() const {
	return new Class(*this);
}

void Class::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);

	SmartPointer<Figure*> smartPointer(this->CreateIterator());

	while (!smartPointer->IsDone()) {
		if (dynamic_cast<Line*>(smartPointer->Current())) {
			static_cast<Line*>(smartPointer->Current())->Accept(visitor, pDC);
		}

		else if (dynamic_cast<Template*>(smartPointer->Current())) {
			static_cast<Template*>(smartPointer->Current())->Accept(visitor, pDC);
		}

		else if (dynamic_cast<ClassName*>(smartPointer->Current())) {
			static_cast<ClassName*>(smartPointer->Current())->Accept(visitor, pDC);
		}

		else if (dynamic_cast<Attribute*>(smartPointer->Current())) {
			static_cast<Attribute*>(smartPointer->Current())->Accept(visitor, pDC);
		}

		else if (dynamic_cast<Method*>(smartPointer->Current())) {
			static_cast<Method*>(smartPointer->Current())->Accept(visitor, pDC);
		}

		else if (dynamic_cast<Reception*>(smartPointer->Current())) {
			static_cast<Reception*>(smartPointer->Current())->Accept(visitor, pDC);
		}

		else if (dynamic_cast<Generalization*>(smartPointer->Current())) {
			static_cast<Generalization*>(smartPointer->Current())->Accept(visitor, pDC);
		}

		else if (dynamic_cast<Realization*>(smartPointer->Current())) {
			static_cast<Realization*>(smartPointer->Current())->Accept(visitor, pDC);
		}


		else if (dynamic_cast<Dependency*>(smartPointer->Current())) {
			static_cast<Dependency*>(smartPointer->Current())->Accept(visitor, pDC);
		}


		else if (dynamic_cast<Association*>(smartPointer->Current())) {
			static_cast<Association*>(smartPointer->Current())->Accept(visitor, pDC);
		}


		else if (dynamic_cast<DirectedAssociation*>(smartPointer->Current())) {
			static_cast<DirectedAssociation*>(smartPointer->Current())->Accept(visitor, pDC);
		}


		else if (dynamic_cast<Aggregation*>(smartPointer->Current())) {
			static_cast<Aggregation*>(smartPointer->Current())->Accept(visitor, pDC);
		}


		else if (dynamic_cast<Aggregations*>(smartPointer->Current())) {
			static_cast<Aggregations*>(smartPointer->Current())->Accept(visitor, pDC);
		}


		else if (dynamic_cast<Composition*>(smartPointer->Current())) {
			static_cast<Composition*>(smartPointer->Current())->Accept(visitor, pDC);

		}

		else if (dynamic_cast<Compositions*>(smartPointer->Current())) {
			static_cast<Compositions*>(smartPointer->Current())->Accept(visitor, pDC);
		}

		else if (dynamic_cast<MemoLine*>(smartPointer->Current())) {
			static_cast<MemoLine*>(smartPointer->Current())->Accept(visitor, pDC);
		}
		else if (dynamic_cast<SelfGeneralization*>(smartPointer->Current())) {
			static_cast<SelfGeneralization*>(smartPointer->Current())->Accept(visitor, pDC);
		}
		else if (dynamic_cast<SelfDependency*>(smartPointer->Current())) {
			static_cast<SelfDependency*>(smartPointer->Current())->Accept(visitor, pDC);
		}
		else if (dynamic_cast<SelfAggregation*>(smartPointer->Current())) {
			static_cast<SelfAggregation*>(smartPointer->Current())->Accept(visitor, pDC);
		}
		else if (dynamic_cast<SelfAssociation*>(smartPointer->Current())) {
			static_cast<SelfAssociation*>(smartPointer->Current())->Accept(visitor, pDC);
		}
		else if (dynamic_cast<SelfAggregations*>(smartPointer->Current())) {
			static_cast<SelfAggregations*>(smartPointer->Current())->Accept(visitor, pDC);
		}
		else if (dynamic_cast<SelfDirectedAssociation*>(smartPointer->Current())) {
			static_cast<SelfDirectedAssociation*>(smartPointer->Current())->Accept(visitor, pDC);
		}
		else if (dynamic_cast<SelfComposition*>(smartPointer->Current())) {
			static_cast<SelfComposition*>(smartPointer->Current())->Accept(visitor, pDC);
		}
		else if (dynamic_cast<SelfCompositions*>(smartPointer->Current())) {
			static_cast<SelfCompositions*>(smartPointer->Current())->Accept(visitor, pDC);
		}

		smartPointer->Next();
	}
}

Long Class::SetMinimumWidth() {
	this->minimumWidth = 120;

	SmartPointer<Figure*> iterator(this->CreateIterator());
	for (iterator->First();!iterator->IsDone();iterator->Next()) {
		if (iterator->Current()->GetMinimumWidth() > this->minimumWidth) {
			this->minimumWidth = iterator->Current()->GetMinimumWidth();
		}
	}
	return this->minimumWidth;
}

Long Class::Correct(Figure *figure, Long index) {
	return index = this->figures.Modify(index, figure);
}