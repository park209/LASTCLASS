//OnVScrollLineUp.cpp

#include "OnVScrollLineUp.h"
#include "ClassDiagramForm.h"

OnVScrollLineUp::OnVScrollLineUp() {
}
OnVScrollLineUp::OnVScrollLineUp(const OnVScrollLineUp& source) {
}
OnVScrollLineUp::~OnVScrollLineUp() {
}

void OnVScrollLineUp::Scrolling(ClassDiagramForm *classDiagramForm) {
	int minpos;
	int maxpos;
	classDiagramForm->GetScrollRange(SB_VERT, &minpos, &maxpos);
	maxpos = classDiagramForm->GetScrollLimit(SB_VERT);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_VERT);

	curpos -= 100;
	if (curpos < minpos) {
		curpos = minpos;
	}

	classDiagramForm->SetScrollPos(SB_VERT, curpos);
}