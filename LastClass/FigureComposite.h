//FigureComposite.h

#ifndef _FIGURECOMPOSITE_H
#define _FIGURECOMPOSTIE_H

#include "Array.h"
#include "Figure.h"
#include "ArrayIterator.h"
#include "SmartPointer.h"

typedef signed long int Long;

class FigureComposite : public Figure {
public:
	FigureComposite(Long capcity = 256);
	FigureComposite(const FigureComposite& source);
	virtual ~FigureComposite() = 0;

	virtual Figure* Clone() const = 0;
	ArrayIterator<Figure*>* CreateIterator() const;

    virtual	Long Add(Figure *figure) = 0;
	virtual Long Add(Long x, Long y, Long width, Long height) = 0;
	virtual Long Remove(Long index) = 0;
	virtual Figure* GetAt(Long index) = 0;

	//virtual FigureComposite& operator = (const FigureComposite& source) = 0;

protected:
	Array<Figure*> figures;
	Long capacity;
	Long length;
};

#endif //_FIGURECOMOSITE_H