//OnHScrollRight.h

#ifndef _ONHSCROLLRIGHT_H
#define _ONHSCROLLRIGHT_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnHScrollRight : public ScrollAction {
public:
	OnHScrollRight();
	OnHScrollRight(const OnHScrollRight& sorce);
	OnHScrollRight& operator=(const OnHScrollRight& source);
	virtual ~OnHScrollRight();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONHSCROLLRIGHT_H





