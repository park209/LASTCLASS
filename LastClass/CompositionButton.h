//CompositionButton.h


#ifndef _COMPOSITIONBUTTON_H
#define _COMPOSITIONBUTTON_H


#include"ButtonState.h"
class Selection;
typedef signed long int Long;



class CompositionButton : public ButtonState {
public:

	CompositionButton();
	CompositionButton(const CompositionButton& source);
	virtual ~CompositionButton();

	virtual void ChangeState(DrawingController *drawingController, Long key);
	virtual void AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);

	CompositionButton& operator=(const CompositionButton& source);
};


#endif //!_COMPOSITIONBUTTON_H
