//PrintPreviewPrintButton.cpp

#include "PrintPreviewPrintButton.h"
#include "PrintPreview.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Diagram.h"
#include "Finder.h"
#include "FigureComposite.h"
#include "Relation.h"

PrintPreviewPrintButton::PrintPreviewPrintButton() {
}

PrintPreviewPrintButton::PrintPreviewPrintButton(const PrintPreviewPrintButton& source) {
}

PrintPreviewPrintButton::~PrintPreviewPrintButton() {
}

void PrintPreviewPrintButton::ButtonPress(PrintPreview *printPreview) {

	CPrintDialog printDialog(FALSE, PD_ALLPAGES | PD_RETURNDC, printPreview);


	INT_PTR int_ptr = AfxGetApp()->DoPrintDialog(&printDialog);


	if (int_ptr == IDOK) {
		bool ret = false;
		CRect rect(0, 0, printPreview->horizontalPageSize, printPreview->verticalPageSize);
		Long l = 0;
		Long m;
		Long n;
		Long k = 1;
		Finder finder;
		Long length = printPreview->lastClass->classDiagramForm->diagram->GetLength();
		printPreview->totalPage = 0;
		while (printPreview->horizontalPaperSize > rect.left) {
			rect.MoveToY(0);
			while (printPreview->verticalPaperSize > rect.top) {
				ret = false;
				l = 0;
				while (l < length && ret != true) { // 2페이지에 클래스나 메모박스가 있는지 확인.
					FigureComposite *figureComposite = (FigureComposite*)printPreview->lastClass->classDiagramForm->diagram->GetAt(l);
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
					printPreview->totalPage = k;
				}
				k++;
				rect.MoveToY(rect.top + printPreview->verticalPageSize);
			}
			rect.MoveToX(rect.left + printPreview->horizontalPageSize);
		}
		CDC dc;
		int count = printDialog.GetCopies();
		Long i = 1;
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

		Info.m_rectDraw.SetRect(0, 0, dc.GetDeviceCaps(HORZRES), dc.GetDeviceCaps(VERTRES));
		Info.SetMaxPage(printPreview->totalPage);
		printPreview->OnBeginPrinting(&dc, &Info);
		i = 1;
		while (i <= count) {
			for (UINT page = Info.GetMinPage(); page <= Info.GetMaxPage() && bPrintingOK; page++) {

				dc.StartPage();
				Info.m_nCurPage = page;
				printPreview->OnPrint(&dc, &Info, page);
				bPrintingOK = (dc.EndPage() > 0);

			}
			i++;

		}
		printPreview->OnEndPrinting(&dc, &Info);
		if (bPrintingOK) dc.EndDoc();
		else dc.AbortDoc();

		dc.Detach();
	}

}