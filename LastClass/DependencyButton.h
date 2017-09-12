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

	virtual void ChangeState(DrawingController *drawingController, Long key);
	virtual void AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY);

	DependencyButton& operator=(const DependencyButton& source);
};


#endif //!_DEPENDENCYBUTTON_H
