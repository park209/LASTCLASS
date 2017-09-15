//ClassButton.h
#ifndef _CLASSBUTTON_H
#define _CLASSBUTTON_H

#include"ButtonState.h"

typedef signed long int Long;

class Figure;
class ClassButton : public ButtonState {
public:

	ClassButton();
	ClassButton(const ClassButton& source);
	virtual ~ClassButton();

	virtual void ChangeState(DrawingController *drawingController, UINT nChar);
	virtual Figure* AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	virtual void Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc);

	ClassButton& operator=(const ClassButton& source);
};


#endif //_CLASSBUTTON_H