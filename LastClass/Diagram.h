//Diagram.h

#ifndef _DIAGRAM_H
#define _DIAGRAM_H

#include "Class.h"

class Diagram : public FigureComposite {
public:
	Diagram(Long capacity = 1024);
	virtual ~Diagram();
	Diagram(const Diagram& source);
	Diagram& operator = (const Diagram& source);

	Long Add(Figure *figure);
	Long Add(Long x, Long y, Long width, Long height);
	Long Remove(Long index);
	Figure* GetAt(Long index);
	Figure* Clone();
};

#endif //_DIAGRAM_H