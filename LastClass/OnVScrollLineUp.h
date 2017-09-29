#ifndef _ONVSCROLLLINEUP_H
#define _ONVSCROLLLINEUP_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnVScrollLineUp : public ScrollAction {
public:
	OnVScrollLineUp();
	OnVScrollLineUp(const OnVScrollLineUp& sorce);
	OnVScrollLineUp& operator=(const OnVScrollLineUp& source);
	virtual ~OnVScrollLineUp();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONVSCROLLLINEUP_H
