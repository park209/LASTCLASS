#include "OnVScrollTop.h"
#include "VerticalScrollBar.h"

OnVScrollTop::OnVScrollTop() : ScrollAction() {
}
OnVScrollTop::OnVScrollTop(const OnVScrollTop& source) : ScrollAction(source) {
}
OnVScrollTop::~OnVScrollTop() {
}
OnVScrollTop& OnVScrollTop::operator=(const OnVScrollTop& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnVScrollTop::ScrollScreen(Scroll *scroll) {
	scroll->OnVScrollTop();
}