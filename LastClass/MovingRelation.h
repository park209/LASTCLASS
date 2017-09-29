//MovingRelation.h

#ifndef _MOVINGRELATION_H
#define _MOVINGRELATION_H

#include "MouseLButtonAction.h"

class MovingRelation :public MouseLButtonAction {
public:
	static MouseLButtonAction* Instance();

	virtual void MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *cPatinDC);

protected:
	//DrawingClass();
private:
	static MovingRelation* instance;
};

#endif // !_MOVINGRELATION_H

