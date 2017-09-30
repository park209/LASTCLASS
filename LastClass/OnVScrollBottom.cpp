//OnVScrollBottom.cpp

#include "OnVScrollBottom.h"
#include "VerticalScrollBar.h"

OnVScrollBottom::OnVScrollBottom() : ScrollAction() {
}
OnVScrollBottom::OnVScrollBottom(const OnVScrollBottom& source) : ScrollAction(source) {
}
OnVScrollBottom::~OnVScrollBottom() {
}
OnVScrollBottom& OnVScrollBottom::operator=(const OnVScrollBottom& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnVScrollBottom::ScrollScreen(Scroll *scroll) {
	scroll->OnVScrollBottom();
}