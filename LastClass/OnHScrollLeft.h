//OnHScrollLeft.h

#ifndef _ONHSCROLLLEFT_H
#define _ONHSCROLLLEFT_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnHScrollLeft : public ScrollAction {
public:
	OnHScrollLeft();
	OnHScrollLeft(const OnHScrollLeft& sorce);
	OnHScrollLeft& operator=(const OnHScrollLeft& source);
	virtual ~OnHScrollLeft();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONHSCROLLLEFT_H





