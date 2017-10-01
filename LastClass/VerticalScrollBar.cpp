//VerticalScrollBar.cpp

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
	scrinfo.nMax = 5000;// cRect.bottom - 20;      // 최대값
	scrinfo.nPage = cRect.bottom;//100;      // 페이지단위 증가값
	scrinfo.nPos = 0;//(scrinfo.nMax- scrinfo.nPage)/2;         위치
	this->scrollBar->SetScrollInfo(&scrinfo);
	this->scrollBar->ShowScrollBar(SB_BOTH);
}
VerticalScrollBar::VerticalScrollBar(const VerticalScrollBar& source) :Scroll(source) {
}
void VerticalScrollBar::OnVScrollLineDown() {
	

	SCROLLINFO vScrinfo;
	this->scrollBar->GetScrollInfo(&vScrinfo);

	if ((vScrinfo.nPos + (int)vScrinfo.nPage) < vScrinfo.nMax) {
		Long height = 50;
		vScrinfo.nPos += height;
		if (vScrinfo.nPos + (int)vScrinfo.nPage > vScrinfo.nMax) {
			vScrinfo.nPos = vScrinfo.nMax - height;
		}
	}

	this->scrollBar->SetScrollInfo(&vScrinfo);
	CRect rect;
	this->classDiagramForm->GetClientRect(&rect);
	this->classDiagramForm->ScrollWindow(0, -50, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
}
void VerticalScrollBar::OnVScrollLineUp() {

	SCROLLINFO vScrinfo;
	this->scrollBar->GetScrollInfo(&vScrinfo);

	if (vScrinfo.nPos > vScrinfo.nMin) {
		Long height = 50;
		vScrinfo.nPos -= height;
		if (vScrinfo.nPos < vScrinfo.nMin) {
			vScrinfo.nPos = vScrinfo.nMin;
		}
	}

	this->scrollBar->SetScrollInfo(&vScrinfo);
	CRect rect;
	this->classDiagramForm->GetClientRect(&rect);
	this->classDiagramForm->ScrollWindow(0, 50, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
}
void VerticalScrollBar::OnVScrollPageDown() {
	SCROLLINFO vScrinfo;
	this->scrollBar->GetScrollInfo(&vScrinfo);

	if (vScrinfo.nPos < vScrinfo.nMax) {
		vScrinfo.nPos += vScrinfo.nPage;
		if (vScrinfo.nPos > vScrinfo.nMax) {
			vScrinfo.nPos = vScrinfo.nMax;
		}
	}
	
	this->scrollBar->SetScrollInfo(&vScrinfo);
	CRect rect;
	this->classDiagramForm->GetClientRect(&rect);
	this->classDiagramForm->ScrollWindow(0, -100, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
}
void VerticalScrollBar::OnVScrollPageUp() {
	SCROLLINFO vScrinfo;
	this->scrollBar->GetScrollInfo(&vScrinfo);

	if (vScrinfo.nPos > vScrinfo.nMin) {
		vScrinfo.nPos -= vScrinfo.nPage;
		if (vScrinfo.nPos < vScrinfo.nMin) {
			vScrinfo.nPos = vScrinfo.nMin;
		}
	}

	this->scrollBar->SetScrollInfo(&vScrinfo);
	CRect rect;
	this->classDiagramForm->GetClientRect(&rect);
	this->classDiagramForm->ScrollWindow(0, 100, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
}
void VerticalScrollBar::OnVScrollBottom() {
	SCROLLINFO vScrinfo;
	this->scrollBar->GetScrollInfo(&vScrinfo);

	//if (vScrinfo.nPos < vScrinfo.nMax) {
		vScrinfo.nPos = vScrinfo.nMax - vScrinfo.nPage;
	//	if (vScrinfo.nPos > vScrinfo.nMax) {
	//		vScrinfo.nPos = vScrinfo.nMax;
	//	}
	//}

	this->scrollBar->SetScrollInfo(&vScrinfo);
	CRect rect;
	this->classDiagramForm->GetClientRect(&rect);
	this->classDiagramForm->ScrollWindow(0, -(rect.bottom), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
}											//값 수정해야함.
void VerticalScrollBar::OnVScrollTop() {
	SCROLLINFO vScrinfo;
	this->scrollBar->GetScrollInfo(&vScrinfo);

	//if (vScrinfo.nPos < vScrinfo.nMax) {
	vScrinfo.nPos = vScrinfo.nMin ;
	//	if (vScrinfo.nPos > vScrinfo.nMax) {
	//		vScrinfo.nPos = vScrinfo.nMax;
	//	}
	//}

	this->scrollBar->SetScrollInfo(&vScrinfo);
	CRect rect;
	this->classDiagramForm->GetClientRect(&rect);
	this->classDiagramForm->ScrollWindow(0, rect.top, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
}										//값 수정해야함.
void VerticalScrollBar::OnVScrollEndScroll() {
}
void VerticalScrollBar::OnVScrollThumPosition() {
	SCROLLINFO vScrinfo;
	this->scrollBar->GetScrollInfo(&vScrinfo);

	vScrinfo.nPos = vScrinfo.nTrackPos;
	this->scrollBar->SetScrollInfo(&vScrinfo);
	CRect rect;
	this->classDiagramForm->GetClientRect(&rect);
	this->classDiagramForm->ScrollWindow(0, vScrinfo.nPos, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
}
void VerticalScrollBar::OnVScrollThumbTrack() {
	SCROLLINFO vScrinfo;
	this->scrollBar->GetScrollInfo(&vScrinfo);

	vScrinfo.nPos = vScrinfo.nTrackPos;
	this->scrollBar->SetScrollInfo(&vScrinfo);
	CRect rect;
	this->classDiagramForm->GetClientRect(&rect);
	this->classDiagramForm->ScrollWindow(0, vScrinfo.nPos, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
}
VerticalScrollBar& VerticalScrollBar::operator=(const VerticalScrollBar& source) {
	Scroll::operator=(source);
	return *this;
}
VerticalScrollBar::~VerticalScrollBar() {

}