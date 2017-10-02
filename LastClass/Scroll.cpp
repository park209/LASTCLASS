//Scroll.cpp

#include "Scroll.h"
#include "ClassDiagramForm.h"
Scroll::Scroll(ClassDiagramForm *classDiagramForm) {
	this->classDiagramForm = classDiagramForm;
	this->scrollBar = new CScrollBar;
}
Scroll::Scroll(const Scroll& source) {
	this->classDiagramForm = source.classDiagramForm;
	this->scrollBar = source.scrollBar;
}
Scroll::~Scroll() {
	if (this->scrollBar != 0) {
		delete this->scrollBar;
	}
}
void Scroll::OnVScrollLineDown() {

}
void Scroll::OnVScrollLineUp() {

}
void Scroll::OnVScrollPageDown() {

}
void Scroll::OnVScrollPageUp() {

}
void Scroll::OnVScrollBottom() {

}
void Scroll::OnVScrollTop() {

}
void Scroll::OnVScrollEndScroll() {

}
void Scroll::OnVScrollThumPosition() {

}
void Scroll::OnVScrollThumbTrack() {

}
void Scroll::OnHScrollLineRight() {

}
void Scroll::OnHScrollLineLeft() {

}
void Scroll::OnHScrollPageRight() {

}
void Scroll::OnHScrollPageLeft() {

}
void Scroll::OnHScrollRight() {

}
void Scroll::OnHScrollLeft() {

}
void Scroll::OnHScrollEnd() {

}
void Scroll::OnHScrollThumbPosition() {

}
void Scroll::OnHScrollThumbTrack() {

}
void Scroll::OnMouseWheelUp() {

}
void Scroll::OnMouseWheelDown() {

}
Scroll& Scroll::operator=(const Scroll& source) {
	if (this->scrollBar != NULL) {
		delete this->scrollBar;
	}
	this->classDiagramForm = source.classDiagramForm;
	this->scrollBar = source.scrollBar;
	return *this;
}
Long Scroll::SetScrollPos(Long nPos) {
	return this->scrollBar->SetScrollPos(nPos);
}
Long Scroll::GetScrollPos() {
	return this->scrollBar->GetScrollPos();
}
Long Scroll::GetMaxPos() {
	SCROLLINFO scrollInfo;
	 this->scrollBar->GetScrollInfo(&scrollInfo);
	Long maxPos = scrollInfo.nMax - scrollInfo.nPage;
	return maxPos;
}