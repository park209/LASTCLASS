#include "FilePrintMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Diagram.h"
#include "WritingVisitor.h"
#include "PrintPreview.h"
FilePrintMenuAction::FilePrintMenuAction() {
}
FilePrintMenuAction::~FilePrintMenuAction() {
}
void FilePrintMenuAction::MenuPress(LastClass* lastClass) {
	lastClass->classDiagramForm->selection->DeleteAllItems();
	


	CPrintDialog printDialog(FALSE, PD_ALLPAGES | PD_RETURNDC , lastClass);

	INT_PTR int_ptr = printDialog.DoModal();
	
	if (int_ptr == IDOK) {

		int count = printDialog.GetCopies();
		CDC cdc;
		Long i = 1;
		CString strTitle;
		DOCINFO di;
		CPrintInfo Info;
		BOOL bPrintingOK;
		cdc.Attach(printDialog.GetPrinterDC());
		lastClass->printPreview = new PrintPreview(lastClass);
		while (i <= count) {
			cdc.m_bPrinting = TRUE;

		
			strTitle.LoadString(AFX_IDS_APP_TITLE);
	
			ZeroMemory(&di, sizeof(DOCINFO));
			di.cbSize = sizeof(DOCINFO);
			di.lpszDocName = strTitle;

			bPrintingOK = cdc.StartDoc(&di);

	
			Info.m_rectDraw.SetRect(0, 0, cdc.GetDeviceCaps(HORZRES), cdc.GetDeviceCaps(VERTRES));
			Info.SetMaxPage(2);
			lastClass->printPreview->OnBeginPrinting(&cdc, &Info);
			for (UINT page = Info.GetMinPage(); page <= Info.GetMaxPage() && bPrintingOK; page++) {
				cdc.StartPage();
				Info.m_nCurPage = page;
				//lastClass->printPreview->OnPrint(&dc, &Info, page);

				Long i[10] = { 0,2000,800,800,1600,1600,2400,2400,3200,3200 };
				Long j[10] = { 0,0,0,1000,0,1000,0,1000,0,1000 };
				Long k = page - 1;

				Long width = Info.m_rectDraw.Width();
				Long hegiht = Info.m_rectDraw.Height();
				CDC memDC;
				CRect rect;
				lastClass->classDiagramForm->GetClientRect(&rect);
				CBitmap *pOldBitmap;
				CBitmap bitmap;

				CPaintDC dc(lastClass);

				memDC.CreateCompatibleDC(&dc);
				bitmap.CreateCompatibleBitmap(&dc, 4000, 2000);
				pOldBitmap = memDC.SelectObject(&bitmap);
				memDC.FillSolidRect(CRect(0, 0, 4000, 2000), RGB(255, 255, 255));
				CFont cFont;//CreateFont에 값18을 textEdit의 rowHight로 바꿔야함
				cFont.CreateFont(25, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,// 글꼴 설정
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "맑은 고딕");
				lastClass->SetFont(&cFont, TRUE);
				CFont *oldFont = memDC.SelectObject(&cFont);

				DrawingVisitor drawingVisitor;
				lastClass->classDiagramForm->diagram->Accept(drawingVisitor, &memDC);
				WritingVisitor writingVisitor;
				lastClass->classDiagramForm->diagram->Accept(writingVisitor, &memDC);


				CBitmap *pOldBitmapOne;
				CBitmap bitmapOne;
				CDC memDCOne;
				memDCOne.CreateCompatibleDC(&dc);
				bitmapOne.CreateCompatibleBitmap(&dc, 2000, 2000);
				pOldBitmapOne = memDCOne.SelectObject(&bitmapOne);
				memDCOne.FillSolidRect(CRect(0, 0, 2000, 2000), RGB(255, 255, 255));
				memDCOne.BitBlt(0, 0, 2000, 2000, &memDC, i[k], j[k], SRCCOPY);

				int mapMode = cdc.GetMapMode();
				memDCOne.SetMapMode(mapMode);
				cdc.SetStretchBltMode(COLORONCOLOR);

				cdc.StretchBlt(100, 100, width - 200, hegiht - 200, &memDCOne, 0, 0, 2000, 2000, SRCCOPY);


				bPrintingOK = (cdc.EndPage() > 0);
			}
			i++;
		}
		lastClass->printPreview->OnEndPrinting(&cdc, &Info);
		if (bPrintingOK) cdc.EndDoc();
		else cdc.AbortDoc();

		//dc.DeleteDC();
		cdc.Detach();
		
	}
	//printDialog.EndDialog(0);
	if (lastClass->printPreview != NULL) {
		delete lastClass->printPreview;
		lastClass->printPreview = NULL;
	}
	

}