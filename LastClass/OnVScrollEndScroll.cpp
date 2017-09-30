//OnVScrollEndScroll.cpp

#include "OnVScrollEndScroll.h"
#include "VerticalScrollBar.h"

OnVScrollEndScroll::OnVScrollEndScroll() : ScrollAction() {
}
OnVScrollEndScroll::OnVScrollEndScroll(const OnVScrollEndScroll& source) : ScrollAction(source) {
}
OnVScrollEndScroll::~OnVScrollEndScroll() {
}
OnVScrollEndScroll& OnVScrollEndScroll::operator=(const OnVScrollEndScroll& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnVScrollEndScroll::ScrollScreen(Scroll *scroll) {
	scroll->OnVScrollEndScroll();
}