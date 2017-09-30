
//Relation.h
#ifndef _RELATION_H
#define _RELATION_H


#include "Figure.h"
#include "WritingVisitor.h"
#include "Array.h"
#include <afxwin.h>
typedef signed long int Long;



class Relation : public Figure {



public:
	Relation(Long capacity = 1);
	Relation(const Relation& source);
	Relation(Long x, Long y, Long width, Long height);
	virtual ~Relation() = 0;
	Relation& operator = (const Relation& source);
	Figure* Clone()const = 0;

	//�� �����ϴ°�
	Long Move(Long index, CPoint cPoint);
	CPoint GetAt(Long index);
	Long Add(const CPoint& startCPoint, const CPoint& currentCPoint);
	Long Remove(Long index);
	void MergePoints(Long selectIndex, CPoint cPoint);

	void ReplaceString(string rollNameText, Long rollNameBoxIndex);
	void Accept(Visitor& visitor, CDC *cPaintDc);

	Long GetCapacity() const;
	Long GetLength() const;
public:
	Array<string>* rollNames;
	Array<CPoint>* rollNamePoints;
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