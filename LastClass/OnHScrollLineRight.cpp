//OnHScrollLineRight.cpp

#include "OnHScrollLineRight.h"
#include "ClassDiagramForm.h"

OnHScrollLineRight::OnHScrollLineRight() : ScrollAction() {
}
OnHScrollLineRight::OnHScrollLineRight(const OnHScrollLineRight& source) : ScrollAction(source) {
}
OnHScrollLineRight::~OnHScrollLineRight() {
}
OnHScrollLineRight& OnHScrollLineRight::operator=(const OnHScrollLineRight& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollLineRight::Scrolling(ClassDiagramForm *classDiagramForm) {
	// Get the minimum and maximum scroll-bar positions.
	int minpos;
	int maxpos;
	classDiagramForm->GetScrollRange(SB_HORZ, &minpos, &maxpos);
	maxpos = classDiagramForm->GetScrollLimit(SB_HORZ);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_HORZ);

	if (curpos < maxpos) {
		curpos++;
	}

	classDiagramForm->SetScrollPos(SB_HORZ, curpos);
}