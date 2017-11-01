//Scroll.cpp

#include "Scroll.h"
#include "OnHScrollEnd.h"
#include "OnHScrollLeft.h"
#include "OnHScrollRight.h"
#include "OnHScrollLineLeft.h"
#include "OnHScrollLineRight.h"
#include "OnHScrollPageLeft.h"
#include "OnHScrollPageRight.h"

#include "OnVScrollTop.h"
#include "OnVScrollBottom.h"
#include "OnVScrollEnd.h"
#include "OnVScrollLineUp.h"
#include "OnVScrollLineDown.h"
#include "OnVScrollPageUp.h"
#include "OnVScrollPageDown.h"

#include "ClassDiagramForm.h"
#include "ScrollMovingObject.h"

Scroll::Scroll() {
	this->scrollAction = 0;
}
Scroll::Scroll(const Scroll& source) {
	this->scrollAction = source.scrollAction;
}
Scroll::~Scroll() {
	if (this->scrollAction != 0) {
		delete this->scrollAction;
	}
}
Scroll& Scroll::operator=(const Scroll& source) {
	if (this->scrollAction != 0) {
		delete this->scrollAction;
	}
	this->scrollAction = source.scrollAction;
	return *this;
}

ScrollAction* Scroll::MoveVScroll(ClassDiagramForm *classDiagramForm, UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	switch (nSBCode) {
	case SB_TOP:
		this->scrollAction = new OnVScrollTop;
		break;
	case SB_BOTTOM:
		this->scrollAction = new OnVScrollBottom;
		break;
	case SB_ENDSCROLL:
		this->scrollAction = new OnVScrollEnd;
		break;
	case SB_LINEUP: 
		this->scrollAction = new OnVScrollLineUp;
		break;
	case SB_LINEDOWN:
		this->scrollAction = new OnVScrollLineDown;
		break;
	case SB_PAGEUP:
		this->scrollAction = new OnVScrollPageUp;
		break;
	case SB_PAGEDOWN: 
		this->scrollAction = new OnVScrollPageDown;
		break;
	case SB_THUMBPOSITION:
		classDiagramForm->SetScrollPos(SB_VERT, nPos);
		break;
	case SB_THUMBTRACK:
		classDiagramForm->SetScrollPos(SB_VERT, nPos);
		break;
	default:
		break;
	}
	return this->scrollAction;
}

ScrollAction* Scroll::MoveHScroll(ClassDiagramForm *classDiagramForm, UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	switch (nSBCode) {
	case SB_LEFT:      // Scroll to far left.
		this->scrollAction = new OnHScrollLeft;
		break;
	case SB_RIGHT:      // Scroll to far right.
		this->scrollAction = new OnHScrollRight;
		break;
	case SB_ENDSCROLL:   // End scroll.
		this->scrollAction = new OnHScrollEnd;
		break;
	case SB_LINELEFT:      // Scroll left.
		this->scrollAction = new OnHScrollLineLeft;
		break;
	case SB_LINERIGHT:   // Scroll right.
		this->scrollAction = new OnHScrollLineRight;
		break;
	case SB_PAGELEFT:    // Scroll one page left.
		this->scrollAction = new OnHScrollPageLeft;
		break;
	case SB_PAGERIGHT:      // Scroll one page right.
		this->scrollAction = new OnHScrollPageRight;
		break;
	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		classDiagramForm->SetScrollPos(SB_HORZ, nPos);
		break;
	case SB_THUMBTRACK:  // Drag scroll box to specified position. nPos is the
		classDiagramForm->SetScrollPos(SB_HORZ, nPos);
		break;
	default:
		break;
	}
	// Set the new position of the thumb (scroll box).
	return this->scrollAction;
}