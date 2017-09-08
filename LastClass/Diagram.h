#pragma once

//Diagram.h

#ifndef _DIAGRAM_H
#define _DIAGRAM_H

#include"FigureComposite.h"
#include"DrawingVisitor.h"

class Diagram : public FigureComposite {
public:
	Diagram(Long capacity = 256);
	Diagram(const Diagram& source);
	virtual ~Diagram();

	Diagram& operator = (const Diagram& source);
	Figure* operator [] (Long index);

	Long Find(Long x, Long y);
	virtual Long Add(Figure *figure);
	Long AddClass(Long x, Long y, Long width, Long height);
	Long AddMemoBox(Long x, Long y, Long width, Long height);
	virtual Long Remove(Long index);
	virtual Figure* GetAt(Long index);
	
	virtual Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *cPaintDc);

	Long GetCapacity() ;
	Long GetLength();
};
inline Long Diagram::GetCapacity()  {
	return FigureComposite::GetCapacity();
}
inline Long Diagram::GetLength() {
	return FigureComposite::GetLength();
}
#endif // !_DIAGRAM_H