#include "VerticalScrollBar.h"
#include "ClassDiagramForm.h"
VerticalScrollBar::VerticalScrollBar(ClassDiagramForm *classDiagramForm) :Scroll(classDiagramForm){
	CRect cRect;
	SCROLLINFO  scrinfo;
	classDiagramForm->GetClientRect(&cRect);
	this->scrollBar->Create(SBS_VERT, CRect(cRect.right - 20, cRect.top + 30, cRect.right, cRect.bottom - 20), this->classDiagramForm, 1);

	scrinfo.cbSize = sizeof(scrinfo);
	scrinfo.fMask = SIF_ALL;
	scrinfo.nMin = 0;          // 최소값
	scrinfo.nMax = cRect.bottom - 20;      // 최대값
	scrinfo.nPage = 150;      // 페이지단위 증가값
	scrinfo.nTrackPos = 0;  // 트랙바가 움직일때의 위치값
	scrinfo.nPos = 50;        // 위치
	this->scrollBar->SetScrollInfo(&scrinfo);
	this->scrollBar->ShowScrollBar(SB_BOTH);
}
VerticalScrollBar::VerticalScrollBar(const VerticalScrollBar& source) :Scroll(source) {
}
void VerticalScrollBar::ScrollAction(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	int minpos;
	int maxpos;
	this->scrollBar->GetScrollRange( &minpos, &maxpos);
	maxpos = this->scrollBar->GetScrollLimit();

	// Get the current position of scroll box.
	int curpos = this->scrollBar->GetScrollPos();
	if (nSBCode == SB_LINEDOWN) {
		if (curpos < maxpos)
			curpos++;
	}
	//SCROLLINFO scrollInfo;
	this->scrollBar->SetScrollPos(curpos);
}
VerticalScrollBar& VerticalScrollBar::operator=(const VerticalScrollBar& source) {
	Scroll::operator=(source);
	return *this;
}
VerticalScrollBar::~VerticalScrollBar() {

}