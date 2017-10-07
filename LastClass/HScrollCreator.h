//HScrollCreator.h

#ifndef _HSCROLLCREATOR_H
#define _HSCROLLCREATOR_H

#include <afxwin.h>

class ScrollAction;
class HScrollCreator {
public:
	HScrollCreator();
	HScrollCreator(const HScrollCreator& source);
	~HScrollCreator();

	HScrollCreator& operator = (const HScrollCreator& source);

	ScrollAction* CreatorAction(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);

public:
	ScrollAction *scrollAction;
};
#endif // !_HSCROLLCREATOR_H