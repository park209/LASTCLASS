//OnVScrollThumbPosition.h

#ifndef _ONVSCROLLTUHMBPOSITION_H
#define _ONVSCROLLTUHMBPOSITION_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnVScrollThumbPosition : public ScrollAction {
public:
	OnVScrollThumbPosition();
	OnVScrollThumbPosition(const OnVScrollThumbPosition& sorce);
	OnVScrollThumbPosition& operator=(const OnVScrollThumbPosition& source);
	~OnVScrollThumbPosition();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONVSCROLLTUHMBPOSITION_H





