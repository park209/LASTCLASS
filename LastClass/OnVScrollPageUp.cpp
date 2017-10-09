//OnVScrollPageUp.cpp

#include "OnVScrollPageUp.h"
#include "ClassDiagramForm.h"

OnVScrollPageUp::OnVScrollPageUp() {
}
OnVScrollPageUp::OnVScrollPageUp(const OnVScrollPageUp& source) {
}
OnVScrollPageUp::~OnVScrollPageUp() {
}

void OnVScrollPageUp::Scrolling(ClassDiagramForm *classDiagramForm) {
	int minpos;
	int maxpos;
	classDiagramForm->GetScrollRange(SB_VERT, &minpos, &maxpos);
	maxpos = classDiagramForm->GetScrollLimit(SB_VERT);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_VERT);

	curpos -= 50;
	if (curpos < minpos) {
		curpos = minpos;
	}

	classDiagramForm->SetScrollPos(SB_VERT, curpos);
}