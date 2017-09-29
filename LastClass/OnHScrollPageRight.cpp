#include "OnHScrollPageRight.h"
#include "VerticalScrollBar.h"

OnHScrollPageRight::OnHScrollPageRight() : ScrollAction() {
}
OnHScrollPageRight::OnHScrollPageRight(const OnHScrollPageRight& source) : ScrollAction(source) {
}
OnHScrollPageRight::~OnHScrollPageRight() {
}
OnHScrollPageRight& OnHScrollPageRight::operator=(const OnHScrollPageRight& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollPageRight::ScrollScreen(Scroll *scroll) {
	scroll->OnHScrollPageRight();
}
