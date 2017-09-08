#pragma once

//FigureComposite.h

#ifndef _FIGURECOMPOSITE_H
#define _FIGURECOMPOSTIE_H

#include "Array.h"
#include "Figure.h"
#include "ArrayIterator.h"
//#include "SmartPointer.h"

typedef signed long int Long;

class FigureComposite : public Figure {
public:

	FigureComposite(Long capcity = 256);
	FigureComposite(const FigureComposite& source);
	ArrayIterator<Figure*>* CreateIterator() const;
	FigureComposite& operator = (const FigureComposite& source);


	virtual ~FigureComposite() = 0;
	virtual Figure* Clone() const = 0;
	virtual	Long Add(Figure *figure) = 0; //2개가 좋을듯
	virtual Long Remove(Long index) = 0;
	virtual Figure* GetAt(Long index) = 0;


	Long GetCapacity();
	Long GetLength();

protected:
	Array<Figure*> figures;
	Long capacity;
	Long length;
};

inline Long FigureComposite::GetCapacity() {
	return this->capacity;
}
inline Long FigureComposite::GetLength() {
	return this->length;
}

#endif //_FIGURECOMOSITE_H