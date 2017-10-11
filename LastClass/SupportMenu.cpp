//SupportMenu.cpp

#include "SupportMenu.h"
#include "LastClass.h"

BEGIN_MESSAGE_MAP(SupportMenu, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_BN_CLICKED(1, OnpreviousButton)
	ON_BN_CLICKED(2, OnNextButton)
END_MESSAGE_MAP()
SupportMenu::SupportMenu() {
}
int SupportMenu::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);
	CRect rect;
	this->GetClientRect(&rect);
	CPoint point = rect.CenterPoint();

	this->OnSetFocus(this);
	this->nextButton = new CButton;
	this->nextButton->Create("¡ç", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(point.x - 100,rect.bottom - 80, point.x - 40, rect.bottom - 30), this, 1);
	this->previousButton = new CButton;
	this->previousButton->Create("¡æ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(point.x + 40, rect.bottom - 80 , point.x  + 100, rect.bottom - 30), this, 2);
	this->SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	return 0;
}
void SupportMenu::OnPaint() {
	
}
void SupportMenu::OnClose() {
	if (this->nextButton != 0) {
		delete this->nextButton;
	}
	if (this->previousButton != 0) {
		delete this->previousButton;
	}
	if (this != 0) {
		delete this;
	}
}
void SupportMenu::OnNextButton() {


}
void SupportMenu::OnpreviousButton() {

	
}