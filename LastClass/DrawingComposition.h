#ifndef _DRAWINGCOMPOSITION_H
#define _DRAWINGCOMPOSITION_H
#include "MouseLButtonAction.h"

class DrawingComposition :public MouseLButtonAction {
public:
	static MouseLButtonAction* Instance();

	virtual void MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *cPatinDC);


protected:
	//DrawingClass();
private:
	static DrawingComposition* instance;
};

#endif // !_DRAWINGCOMPOSITION_H

