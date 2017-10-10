#include "PrintPreviewState.h"

PrintPreviewState::PrintPreviewState() {
	m_tracker.m_rect.SetRectEmpty();
	m_tracker.m_nStyle = CRectTracker::hatchedBorder | CRectTracker::resizeOutside;
}
void PrintPreviewState::OnInitialUpdate() {
	CPreviewView::OnInitialUpdate();
}
void PrintPreviewState::OnDraw(CDC* pDC) {
	CPreviewView::OnDraw(pDC);
}