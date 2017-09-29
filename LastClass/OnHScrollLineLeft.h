#ifndef _ONHSCROLLLINELEFT_H
#define _ONHSCROLLLINELEFT_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnHScrollLineLeft : public ScrollAction {
public:
	OnHScrollLineLeft();
	OnHScrollLineLeft(const OnHScrollLineLeft& sorce);
	OnHScrollLineLeft& operator=(const OnHScrollLineLeft& source);
	virtual ~OnHScrollLineLeft();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONHSCROLLLINELEFT_H





