//Unclicked.h
#ifndef _UNCLICKED_H
#define _UNCLICKED_H

#include"ButtonState.h"

typedef signed long int Long;

class Unclicked : public ButtonState {
public:

	Unclicked();
	Unclicked(const Unclicked& source);
	virtual ~Unclicked();

	virtual void ChangeState(DrawingController *drawingController, Long key);
	virtual void AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	virtual void Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc);

	Unclicked& operator=(const Unclicked& source);
};


#endif //_UNCLICKED_H