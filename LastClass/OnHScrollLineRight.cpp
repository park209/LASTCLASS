#include "OnHScrollLineRight.h"
#include "VerticalScrollBar.h"

OnHScrollLineRight::OnHScrollLineRight() : ScrollAction() {
}
OnHScrollLineRight::OnHScrollLineRight(const OnHScrollLineRight& source) : ScrollAction(source) {
}
OnHScrollLineRight::~OnHScrollLineRight() {
}
OnHScrollLineRight& OnHScrollLineRight::operator=(const OnHScrollLineRight& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollLineRight::ScrollScreen(Scroll *scroll) {
	scroll->OnHScrollLineRight();
}
