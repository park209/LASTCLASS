
//DirectAssociationButton.h

#ifndef _DIRECTASSOCIATIONBUTTON_H
#define _DIRECTASSOCIATIONBUTTON_H


#include"ButtonState.h"
class Selection;
typedef signed long int Long;



class DirectAssociationButton : public ButtonState {
public:

	DirectAssociationButton();
	DirectAssociationButton(const DirectAssociationButton& source);
	virtual ~DirectAssociationButton();

	virtual void ChangeState(DrawingController *drawingController, Long key);
	virtual void AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);

	DirectAssociationButton& operator=(const DirectAssociationButton& source);
};


#endif //!_DIRECTASSOCIATIONBUTTON_H
