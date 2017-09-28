#ifndef _DRAWINGDIRECTEDASSOCIATION_H
#define _DRAWINGDIRECTEDASSOCIATION_H
#include "MouseLButtonAction.h"

class DrawingDirectedAssociation :public MouseLButtonAction {
public:
	static MouseLButtonAction* Instance();

	virtual void MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *cPatinDC);


protected:
	//DrawingClass();
private:
	static DrawingDirectedAssociation* instance;
};

#endif // !_DRAWINGDIRECTEDASSOCIATION_H

