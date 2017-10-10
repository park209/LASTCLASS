//OnHScrollLineLeft.cpp

#include "OnHScrollLineLeft.h"
#include "ClassDiagramForm.h"

OnHScrollLineLeft::OnHScrollLineLeft() : ScrollAction() {
}
OnHScrollLineLeft::OnHScrollLineLeft(const OnHScrollLineLeft& source) : ScrollAction(source) {
}
OnHScrollLineLeft::~OnHScrollLineLeft() {
}
OnHScrollLineLeft& OnHScrollLineLeft::operator=(const OnHScrollLineLeft& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollLineLeft::Scrolling(ClassDiagramForm *classDiagramForm) {
	// Get the minimum and maximum scroll-bar positions.
	int minpos;
	int maxpos;
	classDiagramForm->GetScrollRange(SB_HORZ, &minpos, &maxpos);
	maxpos = classDiagramForm->GetScrollLimit(SB_HORZ);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_HORZ);

	curpos -= 100;
	if (curpos < minpos) {
		curpos = minpos;
	}

	classDiagramForm->SetScrollPos(SB_HORZ, curpos);
}