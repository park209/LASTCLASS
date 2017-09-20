//Class.cpp
#include "Diagram.h"
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

Class::Class(Long capacity):FigureComposite(capacity) {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->templetePosition = -1;
}

Class::Class(Long x, Long y, Long width, Long height) : FigureComposite(64) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->templetePosition = -1;
}

Class::Class(const Class& source) : FigureComposite(source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->templetePosition = source.templetePosition;
}

Class::~Class() {
}
Figure* Class::Move(Long distanceX, Long distanceY){
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
Figure* Class::AddReception(Diagram *diagram) {

	Line line(this->x, this->y+this->height, this->width, 0);
	
	this->height = height + 50;

	if (this->length < this->capacity) {
		this->figures.Store(this->length, line.Clone());
	}
	else {
		this->figures.AppendFromRear(line.Clone());
		this->capacity++;
	}
	this->length++;
	
	Reception reception(this->x, this->y, this->width,50,"");

	if (this->length < this->capacity) {
		this->figures.Store(this->length, reception.Clone());
	}
	else {
		this->figures.AppendFromRear(reception.Clone());
		this->capacity++;
	}
	this->length++;

	Long i = 0;
	Long j = 0;
	while (i < this->GetLength()) {
		
		if (dynamic_cast<Relation*>(this->GetAt(i))) {
			this->GetAt(i)->Modify(this->GetAt(i)->GetX(), this->GetAt(i)->GetY() + 50, this->GetAt(i)->GetWidth(), this->GetAt(i)->GetHeight() - 50);
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
						figure->EndPointMove(0, 50);
					}
				}
				j++;
		}
		i++;
	}
	return this;
}
Long Class::Remove(Long index) {

	this->length--;
	this->capacity--;

	return this->figures.Delete(index);
}

Figure* Class::GetAt(Long index) {
	return static_cast<Figure*>(this->figures.GetAt(index));
}

Figure* Class::Clone() const{
	return new Class(*this);
}



void Class::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);

	SmartPointer<Figure*> smartPointer(this->CreateIterator());

	while (!smartPointer->IsDone()) {
		if (dynamic_cast<Line*>(smartPointer->Current())){
			static_cast<Line*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		
		else if (dynamic_cast<Template*>(smartPointer->Current())) {
			static_cast<Template*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}

		else if (dynamic_cast<Generalization*>(smartPointer->Current())) {
			static_cast<Generalization*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}

		else if (dynamic_cast<Realization*>(smartPointer->Current())) {
			static_cast<Realization*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
	

		else if (dynamic_cast<Dependency*>(smartPointer->Current())) {
			static_cast<Dependency*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		

		else if (dynamic_cast<Association*>(smartPointer->Current())) {
			static_cast<Association*>(smartPointer->Current())->Accept(visitor, cPaintDc); //, cPaintDc
		}
		

		else if (dynamic_cast<DirectedAssociation*>(smartPointer->Current())) {
			static_cast<DirectedAssociation*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		

		else if (dynamic_cast<Aggregation*>(smartPointer->Current())) {
			static_cast<Aggregation*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		

		else if (dynamic_cast<Aggregations*>(smartPointer->Current())) {
			static_cast<Aggregations*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		

		else if (dynamic_cast<Composition*>(smartPointer->Current())) {
			static_cast<Composition*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		
		}

		else if (dynamic_cast<Compositions*>(smartPointer->Current())) {
			static_cast<Compositions*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}

		else if (dynamic_cast<MemoLine*>(smartPointer->Current())) {
			static_cast<MemoLine*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		else if (dynamic_cast<SelfGeneralization*>(smartPointer->Current())) {
			static_cast<SelfGeneralization*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		else if(dynamic_cast<SelfDependency*>(smartPointer->Current())) {
			static_cast<SelfDependency*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		else if (dynamic_cast<SelfAggregation*>(smartPointer->Current())) {
			static_cast<SelfAggregation*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		else if (dynamic_cast<SelfAssociation*>(smartPointer->Current())) {
			static_cast<SelfAssociation*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		else if (dynamic_cast<SelfAggregations*>(smartPointer->Current())) {
			static_cast<SelfAggregations*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		else if (dynamic_cast<SelfDirectedAssociation*>(smartPointer->Current())) {
			static_cast<SelfDirectedAssociation*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		else if (dynamic_cast<SelfComposition*>(smartPointer->Current())) {
			static_cast<SelfComposition*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		else if (dynamic_cast<SelfCompositions*>(smartPointer->Current())) {
			static_cast<SelfCompositions*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
	
		smartPointer->Next();
	}
}
