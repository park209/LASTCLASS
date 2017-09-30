//OnHScrollLineRight.h

#ifndef _ONHSCROLLLINERIGHT_H
#define _ONHSCROLLLINERIGHT_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnHScrollLineRight : public ScrollAction {
public:
	OnHScrollLineRight();
	OnHScrollLineRight(const OnHScrollLineRight& sorce);
	OnHScrollLineRight& operator=(const OnHScrollLineRight& source);
	virtual ~OnHScrollLineRight();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONHSCROLLLINERIGHT_H





