#ifndef _DRAWINGRELATIONPOINT_H
#define _DRAWINGRELATIONPOINT_H
#include "MouseLButtonAction.h"

class DrawingRelationPoint :public MouseLButtonAction {
public:
	static MouseLButtonAction* Instance();

	virtual void MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPatinDC);

protected:
	//DrawingClass();
private:
	static DrawingRelationPoint* instance;
};
#endif // !_DRAWINGRELATIONPOINT_H

