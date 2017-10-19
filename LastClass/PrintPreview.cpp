//PrintPreview.cpp

#include "PrintPreview.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Relation.h"
#include "DrawingVisitor.h"
#include "WritingVisitor.h"
#include "Diagram.h"
#include "Finder.h"
#include "PrintPreviewButton.h"
#include "PrintPreviewButtonAction.h"

//#include <afxwin.h>
//#include <afxdlgs.h>

BEGIN_MESSAGE_MAP(PrintPreview, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_CLOSE()
	ON_COMMAND_RANGE(1, 5, OnCommandButton)
END_MESSAGE_MAP()

PrintPreview::PrintPreview(LastClass *lastClass) {
	this->lastClass = lastClass;
	this->printPreviewButton = NULL;

	this->nextButton = NULL;
	this->previousButton = NULL;
	this->printButton = NULL;
	this->printZoomIn = NULL;
	this->printZoomOut = NULL;

	this->horizontalPage = 0;
	this->verticalPage = 0;
	this->horizontalPageSize = 2000;
	this->verticalPageSize = 2000;
	this->horizontalPaperSize = 4000;
	this->verticalPaperSize = 2000;
	this->zoomRate = 100;
	this->totalPage=0;
	this->currentPage = 1;
}

int PrintPreview::OnCreate(LPCREATESTRUCT lpCreateStruct) { 
   CFrameWnd::OnCreate(lpCreateStruct);
  
   this->printPreviewButton = new PrintPreviewButton;

   this->ModifyStyle(0, WS_OVERLAPPEDWINDOW  );
   this->nextButton = new CButton;
   this->nextButton->Create("다음 페이지", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(775, 10, 925, 50), this, 1);
   this->previousButton = new CButton;
   this->previousButton->Create("이전 페이지", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(420, 10, 570, 50), this, 2);
   this->printButton = new CButton;
   this->printButton->Create("인쇄하기", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(600, 10, 745, 50), this, 3);
   this->printZoomIn = new CButton;
   //this->printZoomIn->Create("확 대", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(50, 250, 200, 290), this, 4);
   this->printZoomOut = new CButton;
  // this->printZoomOut->Create("축 소", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(50, 300, 200, 340), this, 5);

   //this->SetFocus();
   //this->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);

   //this->SetScrollRange(SB_VERT, 0, 380);

   this->lastClass->EnableWindow(false);
   //this->lastClass->classDiagramForm->EnableWindow(false);


   CRect rect(2000, 0, 4000, 2000);
   bool ret = false;
   Long l = 0;
   Long m;
   Long n;
   Finder finder;
   Long length = lastClass->classDiagramForm->diagram->GetLength();
   while (l < length && ret != true) { // 2페이지에 클래스나 메모박스가 있는지 확인.
	   FigureComposite *figureComposite = (FigureComposite*)lastClass->classDiagramForm->diagram->GetAt(l);
	   CRect comperRect(figureComposite->GetX(), figureComposite->GetY(), figureComposite->GetX() + figureComposite->GetWidth(), figureComposite->GetY() + figureComposite->GetHeight());
	   ret = finder.FindRectangleByArea(comperRect, rect);
	   m = 0;
	   while (m < figureComposite->GetLength() && ret != true) {
		   Figure *figure = figureComposite->GetAt(m);
		   ret = finder.FindRectangleByPoint(rect, figure->GetX(), figure->GetY());
		   if (dynamic_cast<Relation*>(figure)) {
			   Relation *relation = static_cast<Relation*>(figure);
			   n = 0;
			   while (n < relation->GetLength() && ret != true) {
				   CPoint point1 = relation->GetAt(n);
				   ret = finder.FindRectangleByPoint(rect, point1.x, point1.y);
				   n++;
			   }
		   }
		   m++;
	   }
	   l++;
   }
   if (ret == true) {
	   this->verticalPaperSize = 2000;
	  this->horizontalPaperSize = 4000;
	   this->totalPage = 2;
   }
   else {
	   this->verticalPaperSize = 2000;
	   this->horizontalPaperSize = 2000;
	   this->totalPage = 1;
   }

   Invalidate(false);
   
   return 0;
}
void PrintPreview::OnPaint() {




	CPaintDC dc(this);
	CRect rec;
	this->GetClientRect(&rec);
	CDC memDC;
	CBitmap *pOldBitmap;
	CBitmap bitmap;
	Long verPaper = this->verticalPaperSize;
	Long horiPaper = this->horizontalPaperSize;
	if (this->verticalPaperSize-this->verticalPage < this->verticalPageSize) {
		verPaper = this->verticalPage + this->verticalPageSize;
	}
	else if (this->verticalPaperSize  < this->verticalPageSize) {
		verPaper = this->verticalPageSize;
	}
	if (this->horizontalPaperSize-this->horizontalPage < this->horizontalPageSize) {
		horiPaper = this->horizontalPage + this->horizontalPageSize;
	}
	else if (this->horizontalPaperSize< this->horizontalPageSize) {
		horiPaper = this->horizontalPageSize;
	}
	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, horiPaper, verPaper);
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(CRect(0, 0, horiPaper, verPaper), RGB(255, 255, 255));
	CFont cFont;//CreateFont에 값18을 textEdit의 rowHight로 바꿔야함
	int ih = MulDiv(14 * lastClass->classDiagramForm->zoomRate / 100, GetDeviceCaps(dc, LOGPIXELSY), 72);
	cFont.CreateFont(ih, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,// 글꼴 설정
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "굴림체");
	SetFont(&cFont, TRUE);
	CFont *oldFont = memDC.SelectObject(&cFont);
	DrawingVisitor drawingVisitor(100);
	this->lastClass->classDiagramForm->diagram->Accept(drawingVisitor, &memDC);
	WritingVisitor writingVisitor(100);
	this->lastClass->classDiagramForm->diagram->Accept(writingVisitor, &memDC);
	// 흰종이 사이즈
	Long a = (rec.CenterPoint().x)* 5 / 8;
	Long b = (rec.CenterPoint().y)* 1 / 6;
	Long c = (rec.CenterPoint().x) * 11 / 8 - (rec.CenterPoint().x) * 5 / 8;
	Long d = (rec.CenterPoint().y) * 11 / 6 - (rec.CenterPoint().y) * 1 / 6;
	
	CBitmap *pOldBitmapOne;
	CBitmap bitmapOne;
	CDC memDCOne;
	memDCOne.CreateCompatibleDC(&dc);
	bitmapOne.CreateCompatibleBitmap(&dc, rec.Width(), rec.Height());
	pOldBitmapOne = memDCOne.SelectObject(&bitmapOne);
	//회색바탕 준비
	memDCOne.FillSolidRect(rec, RGB(153, 153, 153));
	//회색바탕 전체화면으로 출력
	dc.BitBlt(0, 0, rec.Width(), rec.Height(), &memDCOne, 0, 0, SRCCOPY);
	////////////////////////////////////////////////////////////
	//회색바탕 고정하고, 확대한 흰종이에서 이동 가능하게
//	dc.SetMapMode(MM_ISOTROPIC);
	//dc.SetWindowExt(100, 100);
	//dc.SetViewportExt(this->zoomRate, this->zoomRate);
	//dc.SetViewportOrg(220, 20);

	Long vertPos = this->GetScrollPos(SB_VERT);
	//Long horzPos = this->GetScrollPos(SB_HORZ);

	//흰종이 출력
	memDCOne.StretchBlt(a,b ,c,d ,&memDC, this->horizontalPage, this->verticalPage, this->horizontalPageSize, this->verticalPageSize, SRCCOPY);

	//회색바탕에 흰종이 같이 출력
	dc.BitBlt(0, 0, rec.Width(), rec.Height(), &memDCOne, 0, 0, SRCCOPY);

	//CString tempString = _T("");
	//tempString.Format(_T("해상도 (가로:%d 세로:%d), 모니터길이 (가로:%d 세로:%d)"),
	//	dc.GetDeviceCaps(HORZRES),
	//	dc.GetDeviceCaps(VERTRES),
	//	dc.GetDeviceCaps(HORZSIZE),
	//	dc.GetDeviceCaps(VERTSIZE));
	//dc.TextOutA(10, 10, tempString);

	memDC.SelectObject(oldFont);
	cFont.DeleteObject();
	memDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	memDC.DeleteDC();
	memDCOne.SelectObject(pOldBitmap);
	bitmapOne.DeleteObject();
	memDCOne.DeleteDC();
	
}
void PrintPreview::OnDraw(CDC *cdc) {

}
void PrintPreview::OnPrint(CDC *cdc, CPrintInfo *pInfo, UINT page) {
	Long horiPaper = this->horizontalPaperSize;
	Long verPaper = this->verticalPaperSize;
	if (this->horizontalPaperSize % this->horizontalPageSize != 0) {
		horiPaper = (this->horizontalPaperSize / this->horizontalPageSize + 1)*this->horizontalPageSize;
	}
	if (this->verticalPaperSize%this->verticalPageSize != 0) {
		verPaper = (this->verticalPaperSize / this->verticalPageSize + 1)*this->verticalPageSize;
	}
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
	bitmap.CreateCompatibleBitmap(&dc, horiPaper, verPaper);
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(CRect(0, 0, horiPaper, verPaper), RGB(255, 255, 255));
	CFont cFont;//CreateFont에 값18을 textEdit의 rowHight로 바꿔야함
	int ih = MulDiv(14 * lastClass->classDiagramForm->zoomRate / 100, GetDeviceCaps(dc, LOGPIXELSY), 72);
	cFont.CreateFont(ih, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,// 글꼴 설정
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "굴림체");
	SetFont(&cFont, TRUE);
	CFont *oldFont = memDC.SelectObject(&cFont);

	DrawingVisitor drawingVisitor(100);
	this->lastClass->classDiagramForm->diagram->Accept(drawingVisitor, &memDC);
	WritingVisitor writingVisitor(100);
	this->lastClass->classDiagramForm->diagram->Accept(writingVisitor, &memDC);
	Long horiPage = 0;
	Long verPage = 0;
	Long i = 0;
	while (i < page-1) {
		verPage += this->verticalPageSize;
		if (verPage >= verPaper) {
			horiPage += this->horizontalPageSize;
			if (horiPage >= horiPaper) {
				horiPage -= this->horizontalPageSize;
				verPage -= this->verticalPageSize;
			}
			else {
				verPage = 0;
			}
		}
		if (i == 1) {
			Long tth = horiPage;
			Long dee = verPage;
		}
		i++;
	}
		
	CBitmap *pOldBitmapOne;
	CBitmap bitmapOne;
	CDC memDCOne;
	memDCOne.CreateCompatibleDC(&dc);
	bitmapOne.CreateCompatibleBitmap(&dc, this->horizontalPageSize, this->verticalPageSize);
	pOldBitmapOne = memDCOne.SelectObject(&bitmapOne);
	memDCOne.FillSolidRect(CRect(0, 0, this->horizontalPageSize, this->verticalPageSize), RGB(255, 255, 255));
	memDCOne.BitBlt(0, 0, this->horizontalPageSize, this->verticalPageSize, &memDC, horiPage,verPage, SRCCOPY);

	int mapMode = cdc->GetMapMode();
	memDCOne.SetMapMode(mapMode);
	cdc->SetStretchBltMode(COLORONCOLOR);

	//cdc->SetMapMode(MM_ISOTROPIC);
	//cdc->SetWindowExt(100, 100);
	//cdc->SetViewportExt(this->zoomRate, this->zoomRate);

	cdc->StretchBlt(100, 100, width - 200, hegiht - 200, &memDCOne, 0, 0, this->horizontalPageSize, this->verticalPageSize, SRCCOPY);

}

BOOL PrintPreview::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	CFrameWnd::SetFocus();

	SetFocus();
	bool ret = false;

	// nWheelScrollLines 휠 한번에 이동하는 줄 수 (Reg에서 읽어 온다)
	HKEY hKey = 0;
	DWORD dwType = REG_BINARY;
	DWORD dwSize = 10;
	BYTE* pByte = new BYTE[dwSize];

	//ZeroMemory(pByte, dwSize);
	
	//RegOpenKey(HKEY_CURRENT_USER, "Control Panel\\Desktop", &hKey);
	//RegQueryValueEx(hKey, "WheelScrollLines", NULL, &dwType, pByte, &dwSize);
//	RegCloseKey(hKey);

	int nWheelScrollLines = atoi((char*)pByte);
	//delete pByte;

	//int vertCurPos = GetScrollPos(SB_VERT);

	if (GetKeyState(VK_CONTROL) >= 0) {
		if (zDelta <= 0) { //마우스 휠 다운
	//		vertCurPos += nWheelScrollLines * 20;
		}
		else {  //마우스 휠 업
	//		vertCurPos -= nWheelScrollLines * 20;
		}
		ret = true;
	}
	else {
		if (zDelta <= 0) { //마우스 휠 다운
			this->zoomRate += 10;
			this->verticalPageSize += 100;
			if (this->verticalPageSize > 3000) {
				this->verticalPageSize = 3000;
			}
			this->horizontalPageSize += 100;
			if (this->horizontalPageSize > 3000) {
				this->horizontalPageSize = 3000;
			}
			if (this->zoomRate < 50) {
				this->zoomRate = 50;
			}
		}
		else {  //마우스 휠 업
			this->zoomRate -= 10;
			this->verticalPageSize -= 100;
			if (this->verticalPageSize < 1000) {
				this->verticalPageSize = 1000;
			}
			this->horizontalPageSize -= 100;
			if (this->horizontalPageSize < 1000) {
				this->horizontalPageSize = 1000;
			}
			if (this->zoomRate > 190) {
				this->zoomRate = 190;
			}
		}
		ret = true;
	}
	//SetScrollPos(SB_VERT, vertCurPos);
	CRect rect(0, 0, this->horizontalPageSize, this->verticalPageSize);
	Long l = 0;
	Long m;
	Long n;
	Long k=1;
	Finder finder;
	Long length = lastClass->classDiagramForm->diagram->GetLength();
	this->totalPage = 0;
	while (this->horizontalPaperSize > rect.left ){
		rect.MoveToY(0);
		while (this->verticalPaperSize > rect.top) {
			ret = false;
			l = 0;
			while (l < length && ret != true) { // 2페이지에 클래스나 메모박스가 있는지 확인.
				FigureComposite *figureComposite = (FigureComposite*)lastClass->classDiagramForm->diagram->GetAt(l);
				CRect comperRect(figureComposite->GetX(), figureComposite->GetY(), figureComposite->GetX() + figureComposite->GetWidth(), figureComposite->GetY() + figureComposite->GetHeight());
				ret = finder.FindRectangleByArea(comperRect, rect);
				m = 0;
				while (m < figureComposite->GetLength() && ret != true) {
					Figure *figure = figureComposite->GetAt(m);
					ret = finder.FindRectangleByPoint(rect, figure->GetX(), figure->GetY());
					if (dynamic_cast<Relation*>(figure)) {
						Relation *relation = static_cast<Relation*>(figure);
						n = 0;
						while (n < relation->GetLength() && ret != true) {
							CPoint point1 = relation->GetAt(n);
							ret = finder.FindRectangleByPoint(rect, point1.x, point1.y);
							n++;
						}
					}
					m++;
				}
				l++;

			}
			if (ret == true) {
				this->totalPage = k;
			}
			k++;
			rect.MoveToY(rect.top + this->verticalPageSize);
		}
		rect.MoveToX(rect.left+this->horizontalPageSize);
	}
	Invalidate(false);

	return ret;
}

void PrintPreview::OnClose() {
	this->lastClass->EnableWindow(true);
	if (this->nextButton != 0) {
		delete this->nextButton;
		this->nextButton = NULL;
	}
	if (this->printButton != 0) {
		delete this->printButton;
		this->printButton = NULL;
	}
	if (this->previousButton != 0) {
		delete this->previousButton;
		this->previousButton = NULL;
	}
	if (this->printZoomIn != 0) {
		delete this->printZoomIn;
		this->printZoomIn = NULL;
	}
	if (this->printZoomOut != 0) {
		delete this->printZoomOut;
		this->printZoomOut = NULL;
	}
	if (this->lastClass->printPreview != NULL) {
		this->lastClass->printPreview = NULL;
	}
	if (this != NULL) {
		delete this;
	}
}

void PrintPreview::OnBeginPrinting(CDC *pDc, CPrintInfo *pInfo) {
	
}

void PrintPreview::OnEndPrinting(CDC *pDc, CPrintInfo *pInfo) {
	this->lastClass->EnableWindow(true);
	if (this->nextButton != 0) {
		delete this->nextButton;
		this->nextButton = NULL;
	}
	if (this->printButton != 0) {
		delete this->printButton;
		this->printButton = NULL;
	}
	if (this->previousButton != 0) {
		delete this->previousButton;
		this->previousButton = NULL;
	}
	if (this->printZoomIn != 0) {
		delete this->printZoomIn;
		this->printZoomIn = NULL;
	}
	if (this->printZoomOut != 0) {
		delete this->printZoomOut;
		this->printZoomOut = NULL;
	}
	if (this->lastClass->printPreview != NULL) {
		this->lastClass->printPreview = NULL;
	}
	if (this != NULL) {
		delete this;
	}
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

void PrintPreview::OnCommandButton(UINT idNumber) {
	PrintPreviewButtonAction *buttonPressed = this->printPreviewButton->ButtonPressed(idNumber);
	if (buttonPressed != 0) {
		buttonPressed->ButtonPress(this);
	}
}