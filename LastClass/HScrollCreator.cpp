//HScrollCreator.cpp

#include "HScrollCreator.h"
#include "OnHScrollLineRight.h"
#include "OnHScrollLineLeft.h"
#include "OnHScrollPageRight.h"
#include "OnHScrollPageLeft.h"
#include "OnHScrollRight.h"
#include "OnHScrollLeft.h"
#include "OnHScrollEnd.h"
#include "OnHScrollThumbPosition.h"
#include "OnHScrollThumbTrack.h"
HScrollCreator::HScrollCreator() {
	this->scrollAction = 0;
}

HScrollCreator::HScrollCreator(const HScrollCreator& source) {
	this->scrollAction = 0; //임시로 clone만들면 아래꺼로
							//this->keyAction = const_cast<KeyBoard>(source).keyAction.Clone();
}

HScrollCreator::~HScrollCreator() {
	if (this->scrollAction != 0) {
		delete this->scrollAction;
		this->scrollAction = 0;
	}
}

HScrollCreator& HScrollCreator::operator = (const HScrollCreator& source) {
	this->scrollAction = 0;

	return *this;
}

ScrollAction* HScrollCreator::CreatorAction(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	if (this->scrollAction != 0) {
		delete this->scrollAction;
		this->scrollAction = 0;
	}
	
	switch (nSBCode) {
	case SB_LINERIGHT:
		this->scrollAction = new OnHScrollLineRight;
		break;
	case SB_LINELEFT:
		this->scrollAction = new OnHScrollLineLeft;
		break;
	case SB_PAGERIGHT:
		this->scrollAction = new OnHScrollPageRight;
		break;
	case SB_PAGELEFT:
		this->scrollAction = new OnHScrollPageLeft;
		break;
	case SB_RIGHT:
		this->scrollAction = new OnHScrollRight;
		break;
	case SB_LEFT:
		this->scrollAction = new OnHScrollLeft;
		break;
	case SB_ENDSCROLL:
		this->scrollAction = new OnHScrollEnd;
		break;
	case SB_THUMBPOSITION:
		this->scrollAction = new OnHScrollThumbPosition;
		break;
	case SB_THUMBTRACK:
		this->scrollAction = new OnHScrollThumbTrack;
		break;

		
	default:
		break;
		
	}
	return this->scrollAction;
}