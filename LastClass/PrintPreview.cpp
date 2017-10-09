//PrintPreview.cpp

#include "PrintPreview.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "DrawingVisitor.h"
#include "WritingVisitor.h"
#include "Diagram.h"
#include <afxwin.h>

BEGIN_MESSAGE_MAP(PrintPreview,CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
	ON_BN_CLICKED(1,OnNextButton)
	ON_BN_CLICKED(2, OnPriviousButton)
	ON_BN_CLICKED(3, OnPrintButton)
END_MESSAGE_MAP()
PrintPreview::PrintPreview(LastClass *lastClass) {
	this->lastClass = lastClass;
	this->nextButton = NULL;
	this->priviousButton = NULL;
	this->printButton = NULL;
	this->horizontalPage = 0;
	this->verticalPage = 0;
}
int PrintPreview::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);
	this->nextButton = new CButton;
	this->nextButton->Create("다음", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_CENTER|BS_VCENTER,CRect(800,200,880,240), this, 1);
	this->priviousButton = new CButton;
	this->priviousButton->Create("이전", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(800, 250, 880, 290), this, 2);
	this->printButton = new CButton;
	this->printButton->Create("인쇄", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(800, 300, 880, 340), this, 3);
	Invalidate();
	return 0;
}
void PrintPreview::OnPaint() {
	
	CPaintDC dc(this);
	CRect rec;
	this->GetClientRect(&rec);
	CDC memDC;
	CBitmap *pOldBitmap;
	CBitmap bitmap;
	
	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, 4000, 2000);
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(CRect(0, 0, 4000, 2000), RGB(255, 255, 255));
	CFont cFont;//CreateFont에 값18을 textEdit의 rowHight로 바꿔야함
	cFont.CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,// 글꼴 설정
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "맑은 고딕");
	SetFont(&cFont, TRUE);
	CFont *oldFont = memDC.SelectObject(&cFont);
	DrawingVisitor drawingVisitor;
	this->lastClass->classDiagramForm->diagram->Accept(drawingVisitor, &memDC);
	WritingVisitor writingVisitor;
	this->lastClass->classDiagramForm->diagram->Accept(writingVisitor, &memDC);

	dc.FillSolidRect(rec, RGB(153,153,153));
	dc.StretchBlt(10, 10, 600, 800, &memDC, (this->horizontalPage * 800), (this->verticalPage * 1000), 800,1000, SRCCOPY);

	memDC.SelectObject(oldFont);
	cFont.DeleteObject();
	memDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	memDC.DeleteDC();
}
void PrintPreview::OnClose() {

	if (this->nextButton != 0) {
		delete this->nextButton;
	}
	if (this->printButton != 0) {
		delete this->printButton;
	}
	if (this->priviousButton != 0) {
		delete this->priviousButton;
	}
	if (this != 0) {
		delete this;
	}
}
void PrintPreview::OnLButtonDown(UINT nFlags, CPoint point) {
}
void PrintPreview::OnLButtonUp(UINT nFlags, CPoint point) {

}
void PrintPreview::OnNextButton() {
	this->verticalPage++;
	if (this->verticalPage > 1) {
		this->horizontalPage++;
		this->verticalPage = 0;
	}
	if (this->horizontalPage > 4) {
		this->horizontalPage = 4;
		this->verticalPage = 1;
	}
	//RedrawWindow();
	Invalidate(false);
}
void PrintPreview::OnPriviousButton() {
	this->verticalPage--;
	if (this->verticalPage < 0) {
		this->horizontalPage--;
		this->verticalPage = 1;
	}
	if (this->horizontalPage < 0) {
		this->horizontalPage = 0;
		this->verticalPage = 0;
	}
	//RedrawWindow();
	Invalidate(false);
}
void PrintPreview::OnPrintButton() {

}