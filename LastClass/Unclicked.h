//Unclicked.h
#ifndef _UNCLICKED_H
#define _UNCLICKED_H

#include"ButtonState.h"
class Figure;
typedef signed long int Long;

class Unclicked : public ButtonState {
public:

	Unclicked();
	Unclicked(const Unclicked& source);
	virtual ~Unclicked();

	virtual void ChangeState(DrawingController *drawingController, UINT nChar);
	virtual Figure* AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	virtual void Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc);

	Unclicked& operator=(const Unclicked& source);
};


#endif //_UNCLICKED_H