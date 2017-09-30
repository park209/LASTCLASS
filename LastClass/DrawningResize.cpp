#include "DrawingResize.h"


DrawingResize* DrawingResize::instance = 0;

MouseLButtonAction* DrawingResize::Instance() {
	if (instance == 0) {
		instance = new DrawingResize;
	}
	return instance;
}

void DrawingResize::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

}
void DrawingResize::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

}

void DrawingResize::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {
	
}