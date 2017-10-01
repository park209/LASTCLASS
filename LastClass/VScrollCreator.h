//VScrollCreator.h

#ifndef _VSCROLLCREATOR_H
#define _VSCROLLCREATOR_H

#include <afxwin.h>

class ScrollAction;
class VScrollCreator {
public:
	VScrollCreator();
	VScrollCreator(const VScrollCreator& source);
	~VScrollCreator();

	VScrollCreator& operator = (const VScrollCreator& source);

	ScrollAction* CreatorAction(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	
public:
	ScrollAction *scrollAction;
};
#endif // !_VSCROLLCREATOR_H
