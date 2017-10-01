//OnHScrollPageLeft.cpp

#include "OnHScrollPageLeft.h"
#include "VerticalScrollBar.h"

OnHScrollPageLeft::OnHScrollPageLeft() : ScrollAction() {
}
OnHScrollPageLeft::OnHScrollPageLeft(const OnHScrollPageLeft& source) : ScrollAction(source) {
}
OnHScrollPageLeft::~OnHScrollPageLeft() {
}
OnHScrollPageLeft& OnHScrollPageLeft::operator=(const OnHScrollPageLeft& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollPageLeft::ScrollScreen(Scroll *scroll) {
	scroll->OnHScrollPageLeft();
}
