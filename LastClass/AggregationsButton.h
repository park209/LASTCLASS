//AggregationsButton.h

#ifndef _AGGREGATIONSBUTTON_H
#define _AGGREGATIONSBUTTON_H


#include"ButtonState.h"
#include <afxwin.h>
using namespace std;
class Selection;
typedef signed long int Long;
class Figure;


class AggregationsButton : public ButtonState {
public:

	AggregationsButton();
	AggregationsButton(const AggregationsButton& source);
	virtual ~AggregationsButton();

	virtual void ChangeState(DrawingController *drawingController, UINT nChar);
	virtual Figure* AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	virtual void Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc);


	AggregationsButton& operator=(const AggregationsButton& source);
};


#endif //!_AGGREGATIONSBUTTON_H
