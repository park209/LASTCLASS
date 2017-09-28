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
	virtual void ScrollAction(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	Scroll& operator = (const Scroll& source);
protected:
	CScrollBar *scrollBar;
	ClassDiagramForm *classDiagramForm;
};
#endif // !_SCROLL_H
