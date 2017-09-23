#ifndef _DRAWINGMEMOBOX_H
#define _DRAWINGMEMOBOX_H
#include "MouseLButtonAction.h"
class DrawingMemoBox :public MouseLButtonAction {
public:
	static MouseLButtonAction* Instance();

	virtual void MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPatinDC);

protected:
	//DrawingClass();
private:
	static DrawingMemoBox* instance;
};
#endif // !_DRAWINGMEMOBOX_H
