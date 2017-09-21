//MouseLButton.h

#ifndef _MOUSELUTTON_H
#define _MOUSELUTTON_H

#include <afxwin.h>
using namespace std;


class MouseLButtonAction;
class Diagram;
class Selection;
class CPaintDC;
typedef signed long int Long;

class MouseLButton {
public:
	MouseLButton();
	//~MouseLButton();

	void MouseLButtonUp(Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	void MouseLButtonDown(Long startX, Long startY, Long currentX, Long currentY, CPaintDC *cPatinDC);

private:
	friend class  MouseLButtonAction;
	void ChangeState(UINT nChar);
	void ChangeState(MouseLButtonAction *mouseLButtonAction);
private:
	MouseLButtonAction *state;
	UINT buttonState;
};
#endif
