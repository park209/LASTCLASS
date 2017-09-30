//OnHScrollPageRight.h

#ifndef _ONHSCROLLPAGERIGHT_H
#define _ONHSCROLLPAGERIGHT_H
#include "ScrollAction.h"

class VerticalScrollBar;
class OnHScrollPageRight : public ScrollAction {
public:
	OnHScrollPageRight();
	OnHScrollPageRight(const OnHScrollPageRight& sorce);
	OnHScrollPageRight& operator=(const OnHScrollPageRight& source);
	virtual ~OnHScrollPageRight();
	virtual void ScrollScreen(Scroll *scroll);
};
#endif // !_ONHSCROLLPAGERIGHT_H





