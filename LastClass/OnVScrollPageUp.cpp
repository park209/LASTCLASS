#include "OnVScrollPageUp.h"
#include "VerticalScrollBar.h"

OnVScrollPageUp::OnVScrollPageUp() : ScrollAction() {
}
OnVScrollPageUp::OnVScrollPageUp(const OnVScrollPageUp& source) : ScrollAction(source) {
}
OnVScrollPageUp::~OnVScrollPageUp() {
}
OnVScrollPageUp& OnVScrollPageUp::operator=(const OnVScrollPageUp& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnVScrollPageUp::ScrollScreen(Scroll *scroll) {
	scroll->OnVScrollPageUp();
}
