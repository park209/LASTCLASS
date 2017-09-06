#pragma once
//Relation.h
#ifndef _RELATION_H
#define _RELATION_H


#include "Figure.h"
#include "DrawingVisitor.h"

typedef signed long int Long;

enum Type { GENERALIZATION = 1, REALIZATION = 2, DEPENDENCY = 3, ASSOCIATION = 4, DIRECTEDASSOCIATION = 5, AGGREGATION = 6, AGGREGATIONS = 7, COMPOSITION = 8, COMPOSITIONS = 9 };	// 1:일반화 , 2:실체화 ,3:의존 , 4:연관화 ,5:직접연관 , 6:집합 ,7:집합연관 ,8:합성 , 9:복합연관

class Relation : public Figure {



public:
	Relation(Type type);
	Relation(Long x, Long y, Long width, Long height, Type type);
	Relation(const Relation& source);

	virtual ~Relation();
	Relation& operator = (const Relation& source);
	void Accept(Visitor& visitor);// CDC *cPaintDc
	Figure* Clone()const;
	Long GetType()const;
	
private:
	Type type;
};

inline Long Relation::GetType()const {
	return this->type;
}
#endif // !_RELATION_H
