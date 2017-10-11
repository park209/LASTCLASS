//PrintPreview.cpp

#include "PrintPreview.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "DrawingVisitor.h"
#include "WritingVisitor.h"
#include "Diagram.h"
#include "PrintPreviewState.h"
#include "ToolBar.h"
#include <afxwin.h>
#include <afxdlgs.h>
#include <afxpriv.h>
using namespace std;

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
	this->horizontalPageSize = 800;
	this->verticalPageSize = 1000;
}
int PrintPreview::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);
	
	this->ModifyStyle(0, WS_OVERLAPPEDWINDOW  );
	this->nextButton = new CButton;
	this->nextButton->Create("다음", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_CENTER|BS_VCENTER,CRect(150,200,230,240), this, 1);
	this->priviousButton = new CButton;
	this->priviousButton->Create("이전", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(150, 250, 230, 290), this, 2);
	this->printButton = new CButton;
	this->printButton->Create("인쇄", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(150, 300, 230, 340), this, 3);


	this->SetFocus();
	this->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);

	this->lastClass->EnableWindow(false);
	//this->lastClass->classDiagramForm->EnableWindow(false);
	
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

	dc.SetMapMode(MM_ISOTROPIC);
	dc.SetWindowExt(100, 100);
	dc.SetViewportExt(lastClass->classDiagramForm->zoomRate, lastClass->classDiagramForm->zoomRate);

	dc.FillSolidRect(rec, RGB(153,153,153));
	dc.StretchBlt(rec.CenterPoint().x-300, rec.CenterPoint().y-400, 600, 800, &memDC, this->horizontalPage, this->verticalPage , 800,1000, SRCCOPY);

	memDC.SelectObject(oldFont);
	cFont.DeleteObject();
	memDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	memDC.DeleteDC();
	
}
void PrintPreview::OnDraw(CDC *cdc) {


}
void PrintPreview::OnPrint(CDC *cdc, CPrintInfo *pInfo, UINT page) {
	Long i[10] = { 0,2000,800,800,1600,1600,2400,2400,3200,3200 };
	Long j[10] = { 0,0,0,1000,0,1000,0,1000,0,1000 };
	Long k = page - 1;

	Long width = pInfo->m_rectDraw.Width();
	Long hegiht = pInfo->m_rectDraw.Height();
	CDC memDC;
	CRect rect;
	this->lastClass->classDiagramForm->GetClientRect(&rect);
	CBitmap *pOldBitmap;
	CBitmap bitmap;

	CPaintDC dc(this);

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


	CBitmap *pOldBitmapOne;
	CBitmap bitmapOne;
	CDC memDCOne;
	memDCOne.CreateCompatibleDC(&dc);
	bitmapOne.CreateCompatibleBitmap(&dc, 2000, 2000);
	pOldBitmapOne = memDCOne.SelectObject(&bitmapOne);
	memDCOne.FillSolidRect(CRect(0, 0, 2000, 2000), RGB(255, 255, 255));
	memDCOne.BitBlt(0, 0, 2000, 2000, &memDC, i[k], j[k], SRCCOPY);

	int mapMode = cdc->GetMapMode();
	memDCOne.SetMapMode(mapMode);
	cdc->SetStretchBltMode(COLORONCOLOR);

	cdc->StretchBlt(100, 100, width - 200, hegiht - 200, &memDCOne, 0, 0, 2000, 2000, SRCCOPY);

}
void PrintPreview::OnClose() {
	this->lastClass->EnableWindow(true);
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
		this->lastClass->printPreview = NULL;
		delete this;
	}


}
void PrintPreview::OnNextButton() {
	this->verticalPage += this->verticalPageSize;
	if (this->verticalPage >= 2000) {
		this->horizontalPage += this->horizontalPageSize;;
		if (this->horizontalPage >= 4000) {
			this->horizontalPage -= this->horizontalPageSize;
			this->verticalPage -= this->verticalPageSize;
		}
		else {
			this->verticalPage = 0;
		}
	}
	Invalidate(false);
}
void PrintPreview::OnPriviousButton() {
	this->verticalPage -= this->verticalPageSize;
	if (this->verticalPage < 0) {
		this->horizontalPage -= this->horizontalPageSize;
		if (this->horizontalPage < 0) {
			this->horizontalPage = 0;
			this->verticalPage = 0;
		}
		else {
			if (2000 % this->verticalPageSize == 0) {
				this->verticalPage = (2000 / this->verticalPageSize-1)*this->verticalPageSize;
			}
			else {
				this->verticalPage = (2000 / this->verticalPageSize)*this->verticalPageSize;
			}

		}
	}
	Invalidate(false);
}
void PrintPreview::OnBeginPrinting(CDC *pDc, CPrintInfo *pInfo) {
	
}

void PrintPreview::OnEndPrinting(CDC *pDc, CPrintInfo *pInfo) {
	this->lastClass->EnableWindow(true);
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
		this->lastClass->printPreview = NULL;
		delete this;
	}
}
void PrintPreview::OnPrintButton() {

	CPrintDialog printDialog(FALSE, PD_ALLPAGES | PD_USEDEVMODECOPIES);

	INT_PTR int_ptr = printDialog.DoModal();


	if (int_ptr == IDOK) {
		CDC dc;
		dc.Attach(printDialog.GetPrinterDC());
		
		dc.m_bPrinting = TRUE;

		CString strTitle;
		strTitle.LoadString(AFX_IDS_APP_TITLE);
		DOCINFO di;
		ZeroMemory(&di, sizeof(DOCINFO));
		di.cbSize = sizeof(DOCINFO);
		di.lpszDocName = strTitle;

		BOOL bPrintingOK = dc.StartDoc(&di);

		CPrintInfo Info;
		Info.m_rectDraw.SetRect(0, 0, dc.GetDeviceCaps(HORZRES),dc.GetDeviceCaps(VERTRES));
		Info.SetMaxPage(2);
		OnBeginPrinting(&dc, &Info);
		for (UINT page = Info.GetMinPage(); page <= Info.GetMaxPage() && bPrintingOK; page++) {
			dc.StartPage();
			Info.m_nCurPage = page;
			this->OnPrint(&dc,&Info,page);

			bPrintingOK = (dc.EndPage() > 0);

		}
		this->OnEndPrinting(&dc, &Info);
		if (bPrintingOK) dc.EndDoc();
		else dc.AbortDoc();

		//dc.DeleteDC();
		dc.Detach();
	}
		//printDialog.EndDialog(0);
	
}
void PrintPreview::OnSize(UINT nType, int cx, int cy) {
	Invalidate(false);
}
BOOL PrintPreview::DoModal() {
	if (this->GetParent()) {
		this->GetParent()->EnableWindow(FALSE);
		RunModalLoop(MLF_SHOWONIDLE);
		DestroyWindow();
	}
	return TRUE;
}