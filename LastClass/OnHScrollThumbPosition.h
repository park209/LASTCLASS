//OnHScrollThumbPosition.h

#ifndef _ONHSCROLLTHUMBPOSITION_H
#define _ONHSCROLLTHUMBPOSITION_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnHScrollThumbPosition : public ScrollAction {
public:
	OnHScrollThumbPosition();
	OnHScrollThumbPosition(const OnHScrollThumbPosition& sorce);
	OnHScrollThumbPosition& operator=(const OnHScrollThumbPosition& source);
	virtual ~OnHScrollThumbPosition();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONHSCROLLTHUMBPOSITION_H





