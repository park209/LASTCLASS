//VScrollCreator.cpp

#include "VScrollCreator.h"
#include "OnVScrollLineDown.h"
#include "OnVScrollLineUP.h"
#include "OnVScrollPageDown.h"
#include "OnVScrollPageUp.h"
#include "OnVScrollBottom.h"
#include "OnVScrollTop.h"
#include "OnVScrollEndScroll.h"
#include "OnVScrollThumbPosition.h"
#include "OnVScrollThumbTrack.h"

VScrollCreator::VScrollCreator() {
	this->scrollAction = NULL;
}

VScrollCreator::VScrollCreator(const VScrollCreator& source) {
	this->scrollAction = source.scrollAction; //임시로 clone만들면 아래꺼로
						 //this->keyAction = const_cast<KeyBoard>(source).keyAction.Clone();
}

VScrollCreator::~VScrollCreator() {
	if (this->scrollAction != NULL) {
		delete this->scrollAction;
		this->scrollAction = NULL;
	}
}

VScrollCreator& VScrollCreator::operator = (const VScrollCreator& source) {
	this->scrollAction = source.scrollAction;

	return *this;
}

ScrollAction* VScrollCreator::CreatorAction(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	if (this->scrollAction != NULL) {
		delete this->scrollAction;
		this->scrollAction = NULL;
	}
	switch (nSBCode) {
	case SB_LINEDOWN:
		this->scrollAction = new OnVScrollLineDown;
		break;
	case SB_LINEUP:
		this->scrollAction = new OnVScrollLineUp;
		break;
	case SB_PAGEDOWN:
		this->scrollAction = new OnVScrollPageDown;
		break;
	case SB_PAGEUP:
		this->scrollAction = new OnVScrollPageUp;
		break;
	case SB_BOTTOM:
		this->scrollAction = new OnVScrollBottom;
		break;
	case SB_TOP:
		this->scrollAction = new OnVScrollTop;
		break;
	case SB_ENDSCROLL:
		this->scrollAction = new OnVScrollEndScroll;
		break;
	case SB_THUMBPOSITION:
		this->scrollAction = new OnVScrollThumbPosition;
		break;
	case SB_THUMBTRACK:
		this->scrollAction = new OnVScrollThumbTrack;
		break;
	default:
		break;
	}
	return this->scrollAction;
}