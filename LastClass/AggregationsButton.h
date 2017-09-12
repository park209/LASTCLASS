//AggregationsButton.h

#ifndef _AGGREGATIONSBUTTON_H
#define _AGGREGATIONSBUTTON_H


#include"ButtonState.h"
class Selection;
typedef signed long int Long;



class AggregationsButton : public ButtonState {
public:

	AggregationsButton();
	AggregationsButton(const AggregationsButton& source);
	virtual ~AggregationsButton();

	virtual void ChangeState(DrawingController *drawingController, Long key);
	virtual void AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);

	AggregationsButton& operator=(const AggregationsButton& source);
};


#endif //!_AGGREGATIONSBUTTON_H
