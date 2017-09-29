#include "OnHScrollEnd.h"
#include "VerticalScrollBar.h"

OnHScrollEnd::OnHScrollEnd() : ScrollAction() {
}
OnHScrollEnd::OnHScrollEnd(const OnHScrollEnd& source) : ScrollAction(source) {
}
OnHScrollEnd::~OnHScrollEnd() {
}
OnHScrollEnd& OnHScrollEnd::operator=(const OnHScrollEnd& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollEnd::ScrollScreen(Scroll *scroll) {
	scroll->OnHScrollEnd();
}
