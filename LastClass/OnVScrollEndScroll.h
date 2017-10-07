//OnVScrollEndScroll.h

#ifndef _ONVSCROLLENDSCROLL_H
#define _ONVSCROLLENDSCROLL_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnVScrollEndScroll : public ScrollAction {
public:
	OnVScrollEndScroll();
	OnVScrollEndScroll(const OnVScrollEndScroll& sorce);
	OnVScrollEndScroll& operator=(const OnVScrollEndScroll& source);
	 ~OnVScrollEndScroll();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONVSCROLLENDSCROLL_H





