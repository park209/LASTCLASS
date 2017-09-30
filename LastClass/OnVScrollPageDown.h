#ifndef _ONVSCROLLPAGEDOWN_H
#define _ONVSCROLLPAGEDOWN_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnVScrollPageDown : public ScrollAction {
public:
	OnVScrollPageDown();
	OnVScrollPageDown(const OnVScrollPageDown& sorce);
	OnVScrollPageDown& operator=(const OnVScrollPageDown& source);
	virtual ~OnVScrollPageDown();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONVSCROLLPAGEDOWN_H
