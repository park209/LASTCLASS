//GeneralizationButton.h
#ifndef _GENERALIZATIONBUTTON_H
#define _GENERALIZATIONBUTTON_H

#include"ButtonState.h"
#include "Selection.h"
typedef signed long int Long;



class GeneralizationButton : public ButtonState {
public:

	GeneralizationButton();
	GeneralizationButton(const GeneralizationButton& source);
	virtual ~GeneralizationButton();

	virtual void ChangeState(DrawingController *drawingController, Long key);
	virtual void AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);

	GeneralizationButton& operator=(const GeneralizationButton& source);
};


#endif //_GENERALIZATIONBUTTON_H
