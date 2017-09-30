//VerticalScrollBar.h

#ifndef _VRETICALSCROLLBAR_H
#define _VRETICALSCROLLBAR_H

#include "Scroll.h"
class ClassDiagramForm;
class VerticalScrollBar : public Scroll{
public:
	VerticalScrollBar(ClassDiagramForm *classDiagramForm);
	VerticalScrollBar(const VerticalScrollBar& source);
	VerticalScrollBar& operator= (const VerticalScrollBar& source);
	void OnVScrollLineDown();
	void OnVScrollLineUp();
	void OnVScrollPageDown();
	void OnVScrollPageUp();
	void OnVScrollBottom();
	void OnVScrollTop();
	void OnVScrollEndScroll();
	void OnVScrollThumPosition();
	void OnVScrollThumbTrack();
	virtual ~VerticalScrollBar();
};
#endif // !_VRETICALSCROLLBAR_H
