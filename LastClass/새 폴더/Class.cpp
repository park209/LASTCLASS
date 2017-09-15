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
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "Reception.h"

#include "SmartPointer.h"
#include "ArrayIterator.h"
#include "Iterator.h"

Class::Class(Long capacity):FigureComposite(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->templetePosition = -1;
}

Class::Class(Long x, Long y, Long width, Long height) {
	this->capacity = 256;
	this->length = 0;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->templetePosition = -1;
}

Class::Class(const Class& source) {
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
}

Class::~Class() {
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

Long Class::Remove(Long index) {
	return this->figures.Delete(index);
}

Figure* Class::GetAt(Long index) {
	return static_cast<Figure*>(this->figures.GetAt(index));
}

Figure* Class::Clone() const{
	return new Class(*this);
}



void Class::Accept(Visitor& visitor, CDC *cPaintDc) {
	//cout << "Class Accept" << endl;
	visitor.Visit(this, cPaintDc);

	SmartPointer<Figure*> smartPointer(this->CreateIterator());

	while (!smartPointer->IsDone()) {
		if (dynamic_cast<Line*>(smartPointer->Current())){
			dynamic_cast<Line*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}

		else if (dynamic_cast<Generalization*>(smartPointer->Current())) {
			dynamic_cast<Generalization*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}

		else if (dynamic_cast<Realization*>(smartPointer->Current())) {
			dynamic_cast<Realization*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
	

		else if (dynamic_cast<Dependency*>(smartPointer->Current())) {
			dynamic_cast<Dependency*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		

		else if (dynamic_cast<Association*>(smartPointer->Current())) {
			dynamic_cast<Association*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		

		else if (dynamic_cast<DirectedAssociation*>(smartPointer->Current())) {
			dynamic_cast<DirectedAssociation*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		

		else if (dynamic_cast<Aggregation*>(smartPointer->Current())) {
			dynamic_cast<Aggregation*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		

		else if (dynamic_cast<Aggregations*>(smartPointer->Current())) {
			dynamic_cast<Aggregations*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		

		else if (dynamic_cast<Composition*>(smartPointer->Current())) {
			dynamic_cast<Composition*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		
		}

		else if (dynamic_cast<Compositions*>(smartPointer->Current())) {
			dynamic_cast<Compositions*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		else if (dynamic_cast<MemoLine*>(smartPointer->Current())) {
			dynamic_cast<MemoLine*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}


		else if (dynamic_cast<Template*>(smartPointer->Current())) {
			dynamic_cast<Template*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		else if (dynamic_cast<ClassName*>(smartPointer->Current())) {
			dynamic_cast<ClassName*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		else if (dynamic_cast<Attribute*>(smartPointer->Current())) {
			dynamic_cast<Attribute*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		else if (dynamic_cast<Method*>(smartPointer->Current())) {
			dynamic_cast<Method*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}
		else if (dynamic_cast<Reception*>(smartPointer->Current())) {
			dynamic_cast<Reception*>(smartPointer->Current())->Accept(visitor, cPaintDc);
		}

		smartPointer->Next();
	}
}