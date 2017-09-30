#ifndef _SCROLLACTION_H
#define _SCROLLACTION_H

#include <afxwin.h>
typedef signed long int Long;
class Scroll;
class ScrollAction {
public:
	ScrollAction();
	ScrollAction(const ScrollAction& sorce);
	ScrollAction& operator=(const ScrollAction& source);
	virtual ~ScrollAction() = 0;
	virtual void ScrollScreen(Scroll *scroll) = 0;
};
#endif // !_SCROLLACTION_H
