#ifndef _DRAWINGREALIZATION_H
#define _DRAWINGREALIZATION_H
#include "MouseLButtonAction.h"

class DrawingRealization :public MouseLButtonAction {
public:
	static MouseLButtonAction* Instance();

	virtual void MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPatinDC);


protected:
	//DrawingClass();
private:
	static DrawingRealization* instance;
};

#endif // !_DRAWINGREALIZATION_H

