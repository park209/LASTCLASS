//ReceptionButton.h
#ifndef _RECEPTIONBUTTON_H
#define _RECEPTIONBUTTON_H

#include"ButtonState.h"

class Selection;
typedef signed long int Long;
class Figure;


class ReceptionButton : public ButtonState {
public:

	ReceptionButton();
	ReceptionButton(const ReceptionButton& source);
	virtual ~ReceptionButton();

	virtual void ChangeState(DrawingController *drawingController, UINT nChar);
	virtual Figure* AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	virtual void Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc);


	ReceptionButton& operator=(const ReceptionButton& source);
};


#endif //_RECEPTIONBUTTON_H
