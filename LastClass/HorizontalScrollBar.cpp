//HorizontalScrollBar.cpp

#include "HorizontalScrollBar.h"
#include "ClassDiagramForm.h"


HorizontalScrollBar::HorizontalScrollBar(ClassDiagramForm *classDiagramForm) :Scroll(classDiagramForm) {
	CRect cRect;
	SCROLLINFO  scrinfo;
	classDiagramForm->GetClientRect(&cRect);
	this->scrollBar->Create(SBS_HORZ, CRect(cRect.left , cRect.bottom -20, cRect.right - 20, cRect.bottom ), this->classDiagramForm, 1);

	scrinfo.cbSize = sizeof(scrinfo);
	scrinfo.fMask = SIF_ALL;
	scrinfo.nMin = 0;          // 최소값
	scrinfo.nMax = 10000;// cRect.right - 20;      // 최대값
	scrinfo.nPage = cRect.right; // 5;  //100;      // 페이지단위 증가값
	scrinfo.nTrackPos = 0;  // 트랙바가 움직일때의 위치값
	scrinfo.nPos = 0;        // 위치
	this->scrollBar->SetScrollInfo(&scrinfo);
	this->scrollBar->ShowScrollBar(SB_BOTH);
}
HorizontalScrollBar::HorizontalScrollBar(const HorizontalScrollBar& source) :Scroll(source) {
}
HorizontalScrollBar& HorizontalScrollBar::operator=(const HorizontalScrollBar& source) {
	Scroll::operator=(source);
	return *this;
}
void HorizontalScrollBar::OnHScrollLineRight() {
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
	this->classDiagramForm->ScrollWindow(-50, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
}
void HorizontalScrollBar::OnHScrollLineLeft() {

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
	this->classDiagramForm->ScrollWindow(50, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
}
void HorizontalScrollBar::OnHScrollPageRight() {
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
	this->classDiagramForm->ScrollWindow(-100, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
}
void HorizontalScrollBar::OnHScrollPageLeft() {
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
	this->classDiagramForm->ScrollWindow(100, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
}
void HorizontalScrollBar::OnHScrollRight() {
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
	this->classDiagramForm->ScrollWindow(100, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
}									// 값 수정해야함.
void HorizontalScrollBar::OnHScrollLeft() {
	SCROLLINFO vScrinfo;
	this->scrollBar->GetScrollInfo(&vScrinfo);

	vScrinfo.nPos = vScrinfo.nMax - vScrinfo.nPage;

	this->scrollBar->SetScrollInfo(&vScrinfo);
	CRect rect;
	this->classDiagramForm->GetClientRect(&rect);
	this->classDiagramForm->ScrollWindow(-rect.left, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
}											//값 수정해야함.
void HorizontalScrollBar::OnHScrollEnd() {
	
}										//값 수정해야함.
void HorizontalScrollBar::OnHScrollThumbPosition() {
	SCROLLINFO vScrinfo;
	this->scrollBar->GetScrollInfo(&vScrinfo);

	vScrinfo.nPos = vScrinfo.nTrackPos;
	this->scrollBar->SetScrollInfo(&vScrinfo);
	CRect rect;
	this->classDiagramForm->GetClientRect(&rect);
	this->classDiagramForm->ScrollWindow(vScrinfo.nPos, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
}
void HorizontalScrollBar::OnHScrollThumbTrack() {
	SCROLLINFO vScrinfo;
	this->scrollBar->GetScrollInfo(&vScrinfo);

	vScrinfo.nPos = vScrinfo.nTrackPos;
	this->scrollBar->SetScrollInfo(&vScrinfo);
	CRect rect;
	this->classDiagramForm->GetClientRect(&rect);
	this->classDiagramForm->ScrollWindow(vScrinfo.nPos, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
}
HorizontalScrollBar::~HorizontalScrollBar() {

}