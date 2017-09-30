//OnHScrollLineLeft.cpp

#include "OnHScrollLineLeft.h"
#include "VerticalScrollBar.h"

OnHScrollLineLeft::OnHScrollLineLeft() : ScrollAction() {
}
OnHScrollLineLeft::OnHScrollLineLeft(const OnHScrollLineLeft& source) : ScrollAction(source) {
}
OnHScrollLineLeft::~OnHScrollLineLeft() {
}
OnHScrollLineLeft& OnHScrollLineLeft::operator=(const OnHScrollLineLeft& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollLineLeft::ScrollScreen(Scroll *scroll) {
	scroll->OnHScrollLineLeft();
}
