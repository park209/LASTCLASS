//MemoBoxButton.h


#ifndef _MEMOBOXBUTTON_H
#define _MEMOBOXBUTTON_H


#include"ButtonState.h"
class Selection;
typedef signed long int Long;



class MemoBoxButton : public ButtonState {
public:

	MemoBoxButton();
	MemoBoxButton(const MemoBoxButton& source);
	virtual ~MemoBoxButton();

	virtual void ChangeState(DrawingController *drawingController, Long key);
	virtual void AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);

	MemoBoxButton& operator=(const MemoBoxButton& source);
};


#endif //!_MEMOBOXBUTTON_H
