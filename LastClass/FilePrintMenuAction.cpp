#include "FilePrintMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "PrintPreview.h"

FilePrintMenuAction::FilePrintMenuAction() {
}
FilePrintMenuAction::~FilePrintMenuAction() {
}
void FilePrintMenuAction::MenuPress(LastClass* lastClass) {
	lastClass->classDiagramForm->selection->DeleteAllItems();
	


	CPrintDialog printDialog(FALSE, PD_ALLPAGES | PD_USEDEVMODECOPIES);

	INT_PTR int_ptr = printDialog.DoModal();


	if (int_ptr == IDOK) {
		CDC dc;
		lastClass->printPreview = new PrintPreview(lastClass);
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
		lastClass->printPreview->OnBeginPrinting(&dc, &Info);
		for (UINT page = Info.GetMinPage(); page <= Info.GetMaxPage() && bPrintingOK; page++) {
			dc.StartPage();
			Info.m_nCurPage = page;
			lastClass->printPreview->OnPrint(&dc, &Info, page);

			bPrintingOK = (dc.EndPage() > 0);

		}
		lastClass->printPreview->OnEndPrinting(&dc, &Info);
		if (bPrintingOK) dc.EndDoc();
		else dc.AbortDoc();

		//dc.DeleteDC();
		dc.Detach();
	}
	//printDialog.EndDialog(0);
	if (lastClass->printPreview != NULL) {
		delete lastClass->printPreview;
		lastClass->printPreview = NULL;
	}
	

}