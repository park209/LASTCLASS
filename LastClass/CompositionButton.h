//CompositionButton.h


#ifndef _COMPOSITIONBUTTON_H
#define _COMPOSITIONBUTTON_H


#include"ButtonState.h"
class Selection;
typedef signed long int Long;
class Figure;


class CompositionButton : public ButtonState {
public:

	CompositionButton();
	CompositionButton(const CompositionButton& source);
	virtual ~CompositionButton();

	virtual void ChangeState(DrawingController *drawingController, UINT nChar);
	virtual Figure* AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	virtual void Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc);
	CompositionButton& operator=(const CompositionButton& source);
};


#endif //!_COMPOSITIONBUTTON_H
