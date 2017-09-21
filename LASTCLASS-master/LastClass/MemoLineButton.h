
//MemoLineButton.h

#ifndef _MEMOLINEBUTTON_H
#define _MEMOLINEBUTTON_H


#include"ButtonState.h"

class Selection;
typedef signed long int Long;
class Figure;


class MemoLineButton : public ButtonState {
public:

	MemoLineButton();
	MemoLineButton(const MemoLineButton& source);
	virtual ~MemoLineButton();

	virtual void ChangeState(DrawingController *drawingController, UINT nChar);
	virtual Figure* AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	virtual void Draw(Selection *selection, Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc);

	MemoLineButton& operator=(const MemoLineButton& source);
};


#endif //!_MEMOLINEBUTTON_H
