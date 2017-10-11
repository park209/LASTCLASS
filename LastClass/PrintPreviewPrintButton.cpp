//PrintPreviewPrintButton.cpp

#include "PrintPreviewPrintButton.h"
#include "PrintPreview.h"

PrintPreviewPrintButton::PrintPreviewPrintButton() {
}

PrintPreviewPrintButton::PrintPreviewPrintButton(const PrintPreviewPrintButton& source) {
}

PrintPreviewPrintButton::~PrintPreviewPrintButton() {
}

void PrintPreviewPrintButton::ButtonPress(PrintPreview *printPreview) {

	CPrintDialog printDialog(FALSE, PD_ALLPAGES | PD_RETURNDC, printPreview);

	INT_PTR int_ptr = printDialog.DoModal();


	if (int_ptr == IDOK) {
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
		Info.SetMaxPage(2);
		printPreview->OnBeginPrinting(&dc, &Info);

		for (UINT page = Info.GetMinPage(); page <= Info.GetMaxPage() && bPrintingOK; page++) {
			i = 1;
			while (i <= count) {
				dc.StartPage();
				Info.m_nCurPage = page;
				printPreview->OnPrint(&dc, &Info, page);
				bPrintingOK = (dc.EndPage() > 0);
				i++;
			}


		}
		printPreview->OnEndPrinting(&dc, &Info);
		if (bPrintingOK) dc.EndDoc();
		else dc.AbortDoc();

		dc.Detach();
	}

}