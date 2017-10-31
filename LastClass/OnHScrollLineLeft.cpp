//OnHScrollLineLeft.cpp

#include "OnHScrollLineLeft.h"
#include "ClassDiagramForm.h"
#include "ScrollMovingObject.h"

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
	bool ret;
	ScrollMovingObject moving;
	classDiagramForm->GetScrollRange(SB_HORZ, &minpos, &maxpos);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_HORZ);
	int newpos = curpos - 100;
	if (newpos < minpos) {
		newpos = minpos;
	}
	classDiagramForm->SetScrollPos(SB_HORZ, newpos);
	moving.MovingObject(classDiagramForm->diagram,curpos - newpos);


	SCROLLINFO vScinfo;
	classDiagramForm->GetScrollInfo(SB_HORZ, &vScinfo);
	ret = moving.FindHorizontal(classDiagramForm->diagram, vScinfo.nPage);
	if (ret == false) {
		SCROLLINFO vScinfo;
		classDiagramForm->GetScrollInfo(SB_HORZ, &vScinfo);
		vScinfo.nMax -= 100;
		if (vScinfo.nMax < 4000) {
			vScinfo.nMax = 4000;
		}
		classDiagramForm->SetScrollInfo(SB_HORZ, &vScinfo);
	}

}