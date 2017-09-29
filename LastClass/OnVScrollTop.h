#ifndef _ONVSCROLLTOP_H
#define _ONVSCROLLTOP_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnVScrollTop : public ScrollAction {
public:
	OnVScrollTop();
	OnVScrollTop(const OnVScrollTop& sorce);
	OnVScrollTop& operator=(const OnVScrollTop& source);
	virtual ~OnVScrollTop();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONVSCROLLTOP_H





