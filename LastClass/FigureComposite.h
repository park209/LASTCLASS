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
	FigureComposite(Long capcity = 1024);
	FigureComposite(const FigureComposite& source);
	virtual ~FigureComposite() = 0;
	virtual Figure* Clone() = 0;
	virtual void Accept(Visitor& visitor, CDC *cPaintDc) = 0;

    virtual	Long Add(Figure *figure) = 0;
	virtual Long Remove(Long index) = 0;
	virtual Figure* GetAt(Long index) = 0;

	ArrayIterator<Figure*>* CreateIterator() const;

	FigureComposite& operator = (const FigureComposite& source);

	//virtual Long GetCapacity() const = 0;
	//virtual Long GetLength() const = 0;
protected:
	Array<Figure*> figures;
	Long capacity;
	Long length;
};
//
//inline Long FigureComposite::GetCapacity() const {
//	return this->capacity;
//}
//inline Long FigureComposite::GetLength() const {
//	return this->length;
//}

#endif //_FIGURECOMOSITE_H