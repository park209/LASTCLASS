//AggregationButton.h

#ifndef _AGGREGATIONBUTTON_H
#define _AGGREGATIONBUTTON_H


#include"ButtonState.h"
#include <afxwin.h>
using namespace std;
class Selection;
typedef signed long int Long;



class AggregationButton : public ButtonState {
public:

	AggregationButton();
	AggregationButton(const AggregationButton& source);
	virtual ~AggregationButton();

	virtual void ChangeState(DrawingController *drawingController, UINT nChar);
	virtual void AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	virtual void Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc);


	AggregationButton& operator=(const AggregationButton& source);
};


#endif //!_AGGREGATIONBUTTON_H
