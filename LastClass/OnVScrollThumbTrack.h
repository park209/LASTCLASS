//OnVScrollThumbTrack.h

#ifndef _ONVSCROLLTHUMBTRACK_H
#define _ONVSCROLLTHUMBTRACK_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnVScrollThumbTrack : public ScrollAction {
public:
	OnVScrollThumbTrack();
	OnVScrollThumbTrack(const OnVScrollThumbTrack& sorce);
	OnVScrollThumbTrack& operator=(const OnVScrollThumbTrack& source);
	~OnVScrollThumbTrack();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONVSCROLLTHUMBTRACK_H





