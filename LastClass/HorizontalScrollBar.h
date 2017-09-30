//HorizontalScrollBar.h

#ifndef _HORIZONTALSCROLLBAR_H
#define _HORIZONTALSCROLLBAR_H

#include "Scroll.h"
class ClassDiagramForm;

class HorizontalScrollBar : public Scroll {
public:
	HorizontalScrollBar(ClassDiagramForm *classDiagramForm);
	HorizontalScrollBar(const HorizontalScrollBar& source);
	HorizontalScrollBar& operator= (const HorizontalScrollBar& source);
	void OnHScrollLineRight();
	void OnHScrollLineLeft();
	void OnHScrollPageRight();
	void OnHScrollPageLeft();
	void OnHScrollRight();
	void OnHScrollLeft();
	void OnHScrollEnd();
	void OnHScrollThumbTrack();
	void OnHScrollThumbPosition();
	virtual ~HorizontalScrollBar();
};
#endif // !_HORIZONTALSCROLLBAR_H
