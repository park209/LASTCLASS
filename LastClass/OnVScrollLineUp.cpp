//OnVScrollLineUp.cpp

#include "OnVScrollLineUp.h"
#include "VerticalScrollBar.h"

OnVScrollLineUp::OnVScrollLineUp() : ScrollAction() {
}
OnVScrollLineUp::OnVScrollLineUp(const OnVScrollLineUp& source) : ScrollAction(source) {
}
OnVScrollLineUp::~OnVScrollLineUp() {
}
OnVScrollLineUp& OnVScrollLineUp::operator=(const OnVScrollLineUp& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnVScrollLineUp::ScrollScreen(Scroll *scroll) {
	scroll->OnVScrollLineUp();
}
