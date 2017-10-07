//OnHScrollThumbTrack.cpp

#include "OnHScrollThumbTrack.h"
#include "VerticalScrollBar.h"

OnHScrollThumbTrack::OnHScrollThumbTrack() : ScrollAction() {
}
OnHScrollThumbTrack::OnHScrollThumbTrack(const OnHScrollThumbTrack& source) : ScrollAction(source) {
}
OnHScrollThumbTrack::~OnHScrollThumbTrack() {
}
OnHScrollThumbTrack& OnHScrollThumbTrack::operator=(const OnHScrollThumbTrack& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollThumbTrack::ScrollScreen(Scroll *scroll) {
	scroll->OnHScrollThumbTrack();
}
