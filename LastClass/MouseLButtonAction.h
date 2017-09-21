#ifndef _MOUSELBUTTONACTION_H
#define _MOUSELBUTTONACTION_H
#include "MouseLButton.h"

class MouseLButton;
class Diagram;
class Selection;
class CPaintDC;
typedef signed long int Long;

class MouseLButtonAction {
public:
	virtual void MouseLButtonUp(Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) = 0;
	virtual void MouseLButtonDown(Long startX, Long startY, Long currentX, Long currentY, CPaintDC *cPatinDC) = 0;
protected:
	void ChangeState(MouseLButton* mouseLButton, MouseLButtonAction *mouseLButtonAction) {
		mouseLButton->ChangeState(mouseLButtonAction);
	}
};
#endif // !_MOUSELBUTTONACTION_H

