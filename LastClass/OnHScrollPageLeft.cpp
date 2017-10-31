//OnHScrollPageLeft.cpp

#include "OnHScrollPageLeft.h"
#include "ClassDiagramForm.h"
#include "ScrollMovingObject.h"

OnHScrollPageLeft::OnHScrollPageLeft() : ScrollAction() {
}
OnHScrollPageLeft::OnHScrollPageLeft(const OnHScrollPageLeft& source) : ScrollAction(source) {
}
OnHScrollPageLeft::~OnHScrollPageLeft() {
}
OnHScrollPageLeft& OnHScrollPageLeft::operator=(const OnHScrollPageLeft& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollPageLeft::Scrolling(ClassDiagramForm *classDiagramForm) {
	// Get the minimum and maximum scroll-bar positions.
	int minpos;
	int maxpos;
	classDiagramForm->GetScrollRange(SB_HORZ, &minpos, &maxpos);
	maxpos = classDiagramForm->GetScrollLimit(SB_HORZ);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_HORZ);

	// Get the page size. 
	SCROLLINFO   info;
	classDiagramForm->GetScrollInfo(SB_HORZ, &info, SIF_ALL);
	info.nPage = 50;

	if (curpos > minpos) {
		curpos = max(minpos, curpos - (int)info.nPage);
	}

	classDiagramForm->SetScrollPos(SB_HORZ, curpos);
	ScrollMovingObject moving;
	moving.MovingObject(classDiagramForm->diagram, 50);

	bool ret;
	SCROLLINFO hScinfo;
	classDiagramForm->GetScrollInfo(SB_HORZ, &hScinfo);
	ret = moving.FindHorizontal(classDiagramForm->diagram, hScinfo.nPage);
	if (ret == false) {
		//SCROLLINFO hScinfo;
		//classDiagramForm->GetScrollInfo(SB_HORZ, &hScinfo);
		hScinfo.nMax -= 100;
		if (hScinfo.nMax < 4000) {
			hScinfo.nMax = 4000;
		}
		classDiagramForm->SetScrollInfo(SB_HORZ, &hScinfo);
	}
}