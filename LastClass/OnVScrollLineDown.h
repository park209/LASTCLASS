#ifndef _ONVSCROLLLINEDOWN_H
#define _ONVSCROLLLINEDOWN_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnVScrollLineDown : public ScrollAction {
public:
	OnVScrollLineDown();
	OnVScrollLineDown(const OnVScrollLineDown& sorce);
	OnVScrollLineDown& operator=(const OnVScrollLineDown& source);
	virtual ~OnVScrollLineDown() ;
	virtual void ScrollScreen(Scroll *scroll) ;
};
#endif // !_ONVSCROLLLINEDOWN_H
