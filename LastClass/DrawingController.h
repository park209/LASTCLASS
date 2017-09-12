//DrawingController.h
#ifndef _DRAWINGCONTROLLER_H
#define _DRAWINGCONTROLLER_H

typedef signed long int Long;


class Diagram;
class Selection;
class ButtonState;

class DrawingController {
public:
	DrawingController();
	DrawingController(const DrawingController& source);
	~DrawingController();

	void ChangeState(Long key);
	void AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	//void Draw()

	DrawingController& operator=(const DrawingController& source);

public:
	ButtonState *buttonState;

};

#endif //_DRAWINGCONTROLLER_H