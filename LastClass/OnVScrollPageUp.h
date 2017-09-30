//OnVScrollPageUp.h

#ifndef _ONVSCROLLPAGEUP_H
#define _ONVSCROLLPAGEUP_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnVScrollPageUp : public ScrollAction {
public:
	OnVScrollPageUp();
	OnVScrollPageUp(const OnVScrollPageUp& sorce);
	OnVScrollPageUp& operator=(const OnVScrollPageUp& source);
	virtual ~OnVScrollPageUp();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONVSCROLLPAGEUP_H
