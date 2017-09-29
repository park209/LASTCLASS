//HorizontalScroll.h

#ifndef _HORIZONTALSCROLL_H
#define _HORIZONTALSCROLL_H

#include "Scroll.h"
class ClassDiagramForm;

class HorizontalScroll : public Scroll {
public:
	HorizontalScroll(ClassDiagramForm *classDiagramForm);
	HorizontalScroll(const HorizontalScroll& source);
	HorizontalScroll& operator= (const HorizontalScroll& source);
	virtual ~HorizontalScroll();
};
#endif // !_HORIZONTALSCROLL_H
