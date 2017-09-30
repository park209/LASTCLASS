//OnHScrollEnd.h

#ifndef _ONHSCROLLEND_H
#define _ONHSCROLLEND_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnHScrollEnd : public ScrollAction {
public:
	OnHScrollEnd();
	OnHScrollEnd(const OnHScrollEnd& sorce);
	OnHScrollEnd& operator=(const OnHScrollEnd& source);
	virtual ~OnHScrollEnd();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONHSCROLLEND_H





