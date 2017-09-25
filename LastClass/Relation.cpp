//Relation.cpp
#include "Relation.h"
#include "Finder.h"
Relation::Relation(Long capacity):Figure(), points(capacity){
	//this->points;
	this->capacity = capacity;
	this->length = 0;
}


Relation::Relation(const Relation& source) :Figure(source), points(source.points) {
	Long i = 0;
	while (i < source.length) {
		this->points.Modify(i, const_cast<Relation&>(source).points[i]);
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;

}

Relation::Relation(Long x, Long y, Long width, Long height) :Figure(x,y,width,height), points(10) {
	this->capacity = 10;
	this->length = 0;
}
Relation& Relation::operator=(const Relation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	Long i = 0;
	while (i < source.length) {
		this->points.Modify(i, const_cast<Relation&>(source).points[i]);
		i++;
	}
	return *this;
}

Relation::~Relation() {
}

Long Relation::Move(Long index, CPoint cPoint) {
		return this->points.Modify(index, cPoint);
}
CPoint Relation::GetAt(Long index) {
	return this->points.GetAt(index);
}
Long Relation::Add(const CPoint& stratCPoint, const CPoint& currentCPoint) {
	Long index;
	Finder finder;
	if (this->length == 0 ) {
		index = this->points.Store(this->length, currentCPoint);
	}
	else {
		bool ret = false;
		CPoint lineStart(this->x, this->y);
		CPoint lineEnd;

		index = 0;
		while (index < this->length && ret == false) {

			lineEnd.x = this->GetAt(index).x;
			lineEnd.y = this->GetAt(index).y;
			ret = finder.FindLineByPoint(lineStart, lineEnd, stratCPoint.x, stratCPoint.y);
			lineStart.x = lineEnd.x;
			lineStart.y = lineEnd.y;
			index++;
		}

		if (ret == true) {
			index--;
		}

		lineEnd.x = this->width + this->x;
		lineEnd.y = this->height + this->y;
		if (ret == false) {
			ret = finder.FindLineByPoint(lineStart, lineEnd, stratCPoint.x, stratCPoint.y);
		}
		this->points.Insert(index, currentCPoint);
		this->capacity++;
	}
	this->length++;
	return index;
}
Long Relation::Remove(Long index) {
	this->length--;
	this->capacity--;
	return this->points.Delete(index);
}
Long Relation::Find(CPoint cPoint) {
	Long index = -1;
	bool ret;
	Finder finder;
	CRect cRect1(cPoint.x - 5, cPoint.y - 5, cPoint.x + 5, cPoint.y + 5);
	CPoint compare;
	compare.x = this->x;
	compare.y = this->y;

	CRect cRect(compare.x - 5, compare.y - 5, compare.x  +5, compare.y + 5);
	ret = finder.FindRectangleByArea(cRect1, cRect);
	if (ret == true) {
		index = 0;
	}
	Long i = 0;
	while (i < this->length && index == -1) {
		compare.x = this->GetAt(i).x;
		compare.y = this->GetAt(i).y;
		CRect cRect2(compare.x - 5, compare.y - 5, compare.x + 5, compare.y + 5);
		ret = finder.FindRectangleByArea(cRect1, cRect2);
		if (ret == true) {
			index = i;
		}
		i++;
	}
	if (index == -1) {
		compare.x = this->x + this->width;
		compare.y = this->y + this->height;
		CRect cRect3(compare.x - 5, compare.y - 5, compare.x + 5, compare.y + 5);
		ret == finder.FindRectangleByArea(cRect1, cRect3);
		if (ret == true)
		{
			index = this->length;

		}
	}
	return index;

	Long startIndex;
	Long currentIndex;
	
	if (startIndex > currentIndex) {
		Long i = 0;
		Long count = startIndex - currentIndex;
		while (i < count) {
			this->Remove(currentIndex);
			i++;
		}
	}
	if (startIndex < currentIndex) {
		Long i = 0;
		Long count = currentIndex - startIndex;
		while (i < count) {
			this->Remove(startIndex);
			i++;
		}
	}
}