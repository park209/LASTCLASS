//AssociationButton.h

#ifndef _ASSOCIATIONBUTTON_H
#define _ASSOCIATIONBUTTON_H


#include"ButtonState.h"
class Selection;
typedef signed long int Long;



class AssociationButton : public ButtonState {
public:

	AssociationButton();
	AssociationButton(const AssociationButton& source);
	virtual ~AssociationButton();

	virtual void ChangeState(DrawingController *drawingController, Long key);
	virtual void AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);

	AssociationButton& operator=(const AssociationButton& source);
};


#endif //!_ASSOCIATIONBUTTON_H
