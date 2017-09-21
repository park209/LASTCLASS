
//CompositionsButton.h


#ifndef _COMPOSITIONSBUTTON_H
#define _COMPOSITIONSBUTTON_H


#include"ButtonState.h"
class Selection;
typedef signed long int Long;
class Figure;


class CompositionsButton : public ButtonState {
public:

	CompositionsButton();
	CompositionsButton(const CompositionsButton& source);
	virtual ~CompositionsButton();

	virtual void ChangeState(DrawingController *drawingController, UINT nChar);
	virtual Figure* AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	virtual void Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc);


	CompositionsButton& operator=(const CompositionsButton& source);
};


#endif //!_COMPOSITIONSBUTTON_H
