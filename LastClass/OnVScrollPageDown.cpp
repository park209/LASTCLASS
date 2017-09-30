//OnVScrollPageDown.cpp

#include "OnVScrollPageDown.h"
#include "VerticalScrollBar.h"

OnVScrollPageDown::OnVScrollPageDown() : ScrollAction() {
}
OnVScrollPageDown::OnVScrollPageDown(const OnVScrollPageDown& source) : ScrollAction(source) {
}
OnVScrollPageDown::~OnVScrollPageDown() {
}
OnVScrollPageDown& OnVScrollPageDown::operator=(const OnVScrollPageDown& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnVScrollPageDown::ScrollScreen(Scroll *scroll) {
	scroll->OnVScrollPageDown();
}
