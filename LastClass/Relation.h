
//Relation.h
#ifndef _RELATION_H
#define _RELATION_H


#include "Figure.h"
#include "DrawingVisitor.h"
#include "Array.h"
#include <afxwin.h>
typedef signed long int Long;



class Relation : public Figure {



public:
	Relation(Long capacity = 10);
	Relation(const Relation& source);
	Relation(Long x, Long y, Long width, Long height);
	virtual ~Relation() = 0;
	Relation& operator = (const Relation& source);
	Figure* Clone()const = 0;

	//선 점구하는거
	Long Move(Long index, CPoint cPoint);
	CPoint GetAt(Long index);
	Long Add(CPoint cPoint);
	Long Remove(Long index);
	Long Find(CPoint cPoint);
	Long GetCapacity() const;
	Long GetLength() const;

protected:
	Long capacity;
	Long length;
	Array<CPoint> points;
};
inline Long Relation::GetCapacity() const {
	return this->capacity;
}
inline Long Relation::GetLength() const {
	return this->length;
}
#endif // !_RELATION_H