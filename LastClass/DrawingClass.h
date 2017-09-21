#ifndef _DRAWINGCLASS_H
#define _DRAWINGCLASS_H
#include "MouseLButtonAction.h"
class DrawingClass :public MouseLButtonAction {
public:
	static MouseLButtonAction* Instance();

	virtual void MouseLButtonUp(Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDown(Long startX, Long startY, Long currentX, Long currentY, CPaintDC *cPatinDC);

protected:
	//DrawingClass();
private:
	static DrawingClass* instance;
};
#endif // !_DRAWINGCLASS_H

