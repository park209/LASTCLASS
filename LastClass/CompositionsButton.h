
//CompositionsButton.h


#ifndef _COMPOSITIONSBUTTON_H
#define _COMPOSITIONSBUTTON_H


#include"ButtonState.h"
class Selection;
typedef signed long int Long;



class CompositionsButton : public ButtonState {
public:

	CompositionsButton();
	CompositionsButton(const CompositionsButton& source);
	virtual ~CompositionsButton();

	virtual void ChangeState(DrawingController *drawingController, Long key);
	virtual void AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	virtual void Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc);


	CompositionsButton& operator=(const CompositionsButton& source);
};


#endif //!_COMPOSITIONSBUTTON_H
