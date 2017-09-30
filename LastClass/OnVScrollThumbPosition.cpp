//OnVScrollThumbPosition.cpp

#include "OnVScrollThumbPosition.h"
#include "VerticalScrollBar.h"

OnVScrollThumbPosition::OnVScrollThumbPosition() : ScrollAction() {
}
OnVScrollThumbPosition::OnVScrollThumbPosition(const OnVScrollThumbPosition& source) : ScrollAction(source) {
}
OnVScrollThumbPosition::~OnVScrollThumbPosition() {
}
OnVScrollThumbPosition& OnVScrollThumbPosition::operator=(const OnVScrollThumbPosition& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnVScrollThumbPosition::ScrollScreen(Scroll *scroll) {
	scroll->OnVScrollThumPosition();
}