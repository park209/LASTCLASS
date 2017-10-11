//SupportMenu.cpp

#include "SupportMenu.h"
#include "LastClass.h"

BEGIN_MESSAGE_MAP(SupportMenu, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_BN_CLICKED(1, OnNextButton)
	ON_BN_CLICKED(2, OnpreviousButton)
END_MESSAGE_MAP()
SupportMenu::SupportMenu() {
}
int SupportMenu::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);
	CWnd::SetFocus();
	this->OnSetFocus(this);
	this->nextButton = new CButton;
	this->nextButton->Create("다음", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(750, 200, 830, 240), this, 1);
	this->previousButton = new CButton;
	this->previousButton->Create("이전", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(750, 250, 830, 290), this, 2);
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