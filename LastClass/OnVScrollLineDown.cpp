//OnVScrollLineDown.cpp

#include "OnVScrollLineDown.h"
#include "VerticalScrollBar.h"

OnVScrollLineDown::OnVScrollLineDown() : ScrollAction() {
}
OnVScrollLineDown::OnVScrollLineDown(const OnVScrollLineDown& source) : ScrollAction(source) {
}
OnVScrollLineDown::~OnVScrollLineDown() {
}
OnVScrollLineDown& OnVScrollLineDown::operator=(const OnVScrollLineDown& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnVScrollLineDown::ScrollScreen(Scroll *scroll) {
	scroll->OnVScrollLineDown();
}
