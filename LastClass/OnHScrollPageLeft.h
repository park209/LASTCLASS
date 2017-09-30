//OnHScrollPageLeft.h

#ifndef _ONHSCROLLPAGELEFT_H
#define _ONHSCROLLPAGELEFT_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnHScrollPageLeft : public ScrollAction {
public:
	OnHScrollPageLeft();
	OnHScrollPageLeft(const OnHScrollPageLeft& sorce);
	OnHScrollPageLeft& operator=(const OnHScrollPageLeft& source);
	virtual ~OnHScrollPageLeft();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONHSCROLLPAGELEFT_H





