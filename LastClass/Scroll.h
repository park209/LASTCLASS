//Scroll.h

#ifndef _SCROLL_H
#define _SCROLL_H
#include <afxwin.h>

typedef signed long int Long;
class ClassDiagramForm;

class Scroll {
public:
	Scroll(ClassDiagramForm *classDiagramForm);
	Scroll(const Scroll& source);
	virtual ~Scroll() = 0;
	virtual void OnVScrollLineDown();
	virtual void OnVScrollLineUp();
	virtual void OnVScrollPageDown();
	virtual void OnVScrollPageUp();
	virtual void OnVScrollBottom();
	virtual void OnVScrollTop();
	virtual void OnVScrollEndScroll();
	virtual void OnVScrollThumPosition();
	virtual void OnVScrollThumbTrack();
	virtual void OnHScrollLineRight();
	virtual void OnHScrollLineLeft();
	virtual void OnHScrollPageRight();
	virtual void OnHScrollPageLeft();
	virtual void OnHScrollRight();
	virtual void OnHScrollLeft();
	virtual void OnHScrollEnd();
	virtual void OnHScrollThumbPosition();
	virtual void OnHScrollThumbTrack();
	Scroll& operator = (const Scroll& source);
	Long SetScrollPos(Long nPos);
	Long GetScrollPos();
protected:
	ClassDiagramForm *classDiagramForm;
	CScrollBar *scrollBar;
};
#endif // !_SCROLL_H
