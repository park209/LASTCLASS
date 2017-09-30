//OnHScrollThumbPosition.cpp

#include "OnHScrollThumbPosition.h"
#include "VerticalScrollBar.h"

OnHScrollThumbPosition::OnHScrollThumbPosition() : ScrollAction() {
}
OnHScrollThumbPosition::OnHScrollThumbPosition(const OnHScrollThumbPosition& source) : ScrollAction(source) {
}
OnHScrollThumbPosition::~OnHScrollThumbPosition() {
}
OnHScrollThumbPosition& OnHScrollThumbPosition::operator=(const OnHScrollThumbPosition& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollThumbPosition::ScrollScreen(Scroll *scroll) {
	scroll->OnHScrollThumbPosition();
}
