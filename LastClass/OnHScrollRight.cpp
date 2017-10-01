//OnHScrollRight.cpp

#include "OnHScrollRight.h"
#include "VerticalScrollBar.h"

OnHScrollRight::OnHScrollRight() : ScrollAction() {
}
OnHScrollRight::OnHScrollRight(const OnHScrollRight& source) : ScrollAction(source) {
}
OnHScrollRight::~OnHScrollRight() {
}
OnHScrollRight& OnHScrollRight::operator=(const OnHScrollRight& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollRight::ScrollScreen(Scroll *scroll) {
	scroll->OnHScrollRight();
}
