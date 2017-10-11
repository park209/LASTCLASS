//PrintPreviewZoomInButton.cpp

#include "PrintPreviewZoomInButton.h"
#include "PrintPreview.h"

PrintPreviewZoomInButton::PrintPreviewZoomInButton() {
}

PrintPreviewZoomInButton::PrintPreviewZoomInButton(const PrintPreviewZoomInButton& source) {
}

PrintPreviewZoomInButton::~PrintPreviewZoomInButton() {
}

void PrintPreviewZoomInButton::ButtonPress(PrintPreview *printPreview) {
	printPreview->zoomRate += 10;
	if (printPreview->zoomRate > 190) {
		printPreview->zoomRate = 190;
	}
	printPreview->Invalidate(false);
}