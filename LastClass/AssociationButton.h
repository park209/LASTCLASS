//AssociationButton.h

#ifndef _ASSOCIATIONBUTTON_H
#define _ASSOCIATIONBUTTON_H


#include"ButtonState.h"
class Selection;
typedef signed long int Long;
class Figure;


class AssociationButton : public ButtonState {
public:

	AssociationButton();
	AssociationButton(const AssociationButton& source);
	virtual ~AssociationButton();

	virtual void ChangeState(DrawingController *drawingController, UINT nChar);
	virtual Figure* AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	virtual void Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc);

	AssociationButton& operator=(const AssociationButton& source);
};


#endif //!_ASSOCIATIONBUTTON_H
