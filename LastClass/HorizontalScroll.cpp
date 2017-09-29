#include "HorizontalScroll.h"
#include "ClassDiagramForm.h"


HorizontalScroll::HorizontalScroll(ClassDiagramForm *classDiagramForm) :Scroll(classDiagramForm) {
	CRect cRect;
	SCROLLINFO  scrinfo;
	classDiagramForm->GetClientRect(&cRect);
	this->scrollBar->Create(SBS_HORZ, CRect(cRect.left , cRect.bottom -20, cRect.right - 20, cRect.bottom ), this->classDiagramForm, 1);

	scrinfo.cbSize = sizeof(scrinfo);
	scrinfo.fMask = SIF_ALL;
	scrinfo.nMin = 0;          // 최소값
	scrinfo.nMax = cRect.right - 20;      // 최대값
	scrinfo.nPage = 150;      // 페이지단위 증가값
	scrinfo.nTrackPos = 0;  // 트랙바가 움직일때의 위치값
	scrinfo.nPos = 0;        // 위치
	this->scrollBar->SetScrollInfo(&scrinfo);
	this->scrollBar->ShowScrollBar(SB_BOTH);
}
HorizontalScroll::HorizontalScroll(const HorizontalScroll& source) :Scroll(source) {
}
HorizontalScroll& HorizontalScroll::operator=(const HorizontalScroll& source) {
	Scroll::operator=(source);
	return *this;
}
HorizontalScroll::~HorizontalScroll() {

}