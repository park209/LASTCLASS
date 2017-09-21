#ifndef _DRAWNGRELATION_H
#define _DRAWNGRELATION_H
#include "MouseLButtonAction.h"

class DrawingRelation :public MouseLButtonAction {
public:
	static MouseLButtonAction* Instance();

	virtual void MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPatinDC);


protected:
	//DrawingClass();
private:
	static DrawingRelation* instance;
};
#endif // !_DRAWNGRELATION_H

