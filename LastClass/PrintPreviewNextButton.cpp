//PrintPreviewNextButton.cpp

#include "PrintPreviewNextButton.h"
#include "PrintPreview.h"

PrintPreviewNextButton::PrintPreviewNextButton() {
}

PrintPreviewNextButton::PrintPreviewNextButton(const PrintPreviewNextButton& source) {
}

PrintPreviewNextButton::~PrintPreviewNextButton() {
}

void PrintPreviewNextButton::ButtonPress(PrintPreview *printPreview) {
	printPreview->verticalPage += printPreview->verticalPageSize;
	if (printPreview->verticalPage >= 2000) {
		printPreview->horizontalPage += printPreview->horizontalPageSize;;
		if (printPreview->horizontalPage >= 4000) {
			printPreview->horizontalPage -= printPreview->horizontalPageSize;
			printPreview->verticalPage -= printPreview->verticalPageSize;
		}
		else {
			printPreview->verticalPage = 0;
		}
	}
	printPreview->Invalidate(false);
}