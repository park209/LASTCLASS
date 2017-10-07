//OnVScrollBottom.h

#ifndef _ONVSCROLLBOTTOM_H
#define _ONVSCROLLBOTTOM_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnVScrollBottom : public ScrollAction {
public:
	OnVScrollBottom();
	OnVScrollBottom(const OnVScrollBottom& sorce);
	OnVScrollBottom& operator=(const OnVScrollBottom& source);
	virtual ~OnVScrollBottom();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONVSCROLLBOTTOM_H





