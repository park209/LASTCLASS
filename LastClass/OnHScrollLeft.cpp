//OnHScrollLeft.cpp

#include "OnHScrollLeft.h"
#include "VerticalScrollBar.h"

OnHScrollLeft::OnHScrollLeft() : ScrollAction() {
}
OnHScrollLeft::OnHScrollLeft(const OnHScrollLeft& source) : ScrollAction(source) {
}
OnHScrollLeft::~OnHScrollLeft() {
}
OnHScrollLeft& OnHScrollLeft::operator=(const OnHScrollLeft& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollLeft::ScrollScreen(Scroll *scroll) {
	scroll->OnHScrollLeft();
}
