//MemoBoxButton.h


#ifndef _MEMOBOXBUTTON_H
#define _MEMOBOXBUTTON_H


#include"ButtonState.h"
class Selection;
typedef signed long int Long;
class Figure;


class MemoBoxButton : public ButtonState {
public:

	MemoBoxButton();
	MemoBoxButton(const MemoBoxButton& source);
	virtual ~MemoBoxButton();

	virtual void ChangeState(DrawingController *drawingController, UINT nChar);
	virtual Figure* AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	virtual void Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc);
	
	MemoBoxButton& operator=(const MemoBoxButton& source);
};


#endif //!_MEMOBOXBUTTON_H
