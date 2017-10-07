//OnVScrollThumbTrack.cpp

#include "OnVScrollThumbTrack.h"
#include "VerticalScrollBar.h"

OnVScrollThumbTrack::OnVScrollThumbTrack() : ScrollAction() {
}
OnVScrollThumbTrack::OnVScrollThumbTrack(const OnVScrollThumbTrack& source) : ScrollAction(source) {
}
OnVScrollThumbTrack::~OnVScrollThumbTrack() {
}
OnVScrollThumbTrack& OnVScrollThumbTrack::operator=(const OnVScrollThumbTrack& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnVScrollThumbTrack::ScrollScreen(Scroll *scroll) {
	scroll->OnVScrollThumbTrack();
}