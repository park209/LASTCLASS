//ButtonState.h
#ifndef _BUTTONSTATE_H
#define _BUTTONSTATE_H

typedef signed long int Long;

class DrawingController;
class Diagram;
class Selection;

class ButtonState {
public:

	ButtonState();
	ButtonState(const ButtonState& source);
	virtual ~ButtonState();

	virtual void ChangeState(DrawingController *drawingController, Long key);
	virtual void AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);

	ButtonState& operator=(const ButtonState& source);
};

#endif //_BUTTONSTATE_H