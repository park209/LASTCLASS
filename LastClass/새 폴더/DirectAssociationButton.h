
//DirectAssociationButton.h

#ifndef _DIRECTASSOCIATIONBUTTON_H
#define _DIRECTASSOCIATIONBUTTON_H


#include"ButtonState.h"
class Selection;
typedef signed long int Long;
class Figure;


class DirectAssociationButton : public ButtonState {
public:

	DirectAssociationButton();
	DirectAssociationButton(const DirectAssociationButton& source);
	virtual ~DirectAssociationButton();

	virtual void ChangeState(DrawingController *drawingController, UINT nChar);
	virtual Figure* AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	virtual void Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc);

	DirectAssociationButton& operator=(const DirectAssociationButton& source);
};


#endif //!_DIRECTASSOCIATIONBUTTON_H
