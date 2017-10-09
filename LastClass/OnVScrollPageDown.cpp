//OnVScrollPageDown.cpp

#include "OnVScrollPageDown.h"
#include "ClassDiagramForm.h"

OnVScrollPageDown::OnVScrollPageDown() {
}
OnVScrollPageDown::OnVScrollPageDown(const OnVScrollPageDown& source) {
}
OnVScrollPageDown::~OnVScrollPageDown() {
}

void OnVScrollPageDown::Scrolling(ClassDiagramForm *classDiagramForm) {
	int minpos;
	int maxpos;
	classDiagramForm->GetScrollRange(SB_VERT, &minpos, &maxpos);
	maxpos = classDiagramForm->GetScrollLimit(SB_VERT);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_VERT);

	curpos += 50;
	if (curpos > maxpos) {
		curpos = maxpos;
	}

	classDiagramForm->SetScrollPos(SB_VERT, curpos);
}