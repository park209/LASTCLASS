//MouseLButtonAction.h

#ifndef _MOUSELBUTTONACTION_H
#define _MOUSELBUTTONACTION_H

#include "MouseLButton.h"

class MouseLButton;
class Diagram;
class Selection;
typedef signed long int Long;

class MouseLButtonAction {
public:
	virtual void MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) ;
	virtual void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) ;
protected:
	void ChangeState(MouseLButton* mouseLButton, MouseLButtonAction *mouseLButtonAction,UINT nChar=0);
	void ChangeDefault(MouseLButton* mouseLButton);
};
#endif // !_MOUSELBUTTONACTION_H

