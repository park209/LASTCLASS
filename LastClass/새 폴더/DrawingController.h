//DrawingController.h
#ifndef _DRAWINGCONTROLLER_H
#define _DRAWINGCONTROLLER_H
#include <afxwin.h>
using namespace std;
typedef signed long int Long;


class Diagram;
class Selection;
class ButtonState;
class Figure;
class DrawingController {
public:
	DrawingController();
	DrawingController(const DrawingController& source);
	~DrawingController();

	void ChangeState(UINT nChar);
	Figure* AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	void Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc);

	DrawingController& operator=(const DrawingController& source);

public:
	ButtonState *buttonState;

};

#endif //_DRAWINGCONTROLLER_H