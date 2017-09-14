//DependencyButton.h

#ifndef _DEPENDENCYBUTTON_H
#define _DEPENDENCYBUTTON_H


#include"ButtonState.h"
class Selection;
typedef signed long int Long;



class DependencyButton : public ButtonState {
public:

	DependencyButton();
	DependencyButton(const DependencyButton& source);
	virtual ~DependencyButton();

	virtual void ChangeState(DrawingController *drawingController, UINT nChar);
	virtual void AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);
	virtual void Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc);


	DependencyButton& operator=(const DependencyButton& source);
};


#endif //!_DEPENDENCYBUTTON_H
