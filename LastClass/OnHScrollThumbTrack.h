//OnHScrollThumbTrack.h

#ifndef _ONHSCROLLTHUMBTRACK_H
#define _ONHSCROLLTHUMBTRACK_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnHScrollThumbTrack : public ScrollAction {
public:
	OnHScrollThumbTrack();
	OnHScrollThumbTrack(const OnHScrollThumbTrack& sorce);
	OnHScrollThumbTrack& operator=(const OnHScrollThumbTrack& source);
	virtual ~OnHScrollThumbTrack();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONHSCROLLTHUMBTRACK_H





