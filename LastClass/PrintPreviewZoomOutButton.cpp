//PrintPreviewZoomOutButton.cpp

#include "PrintPreviewZoomOutButton.h"
#include "PrintPreview.h"

PrintPreviewZoomOutButton::PrintPreviewZoomOutButton() {
}

PrintPreviewZoomOutButton::PrintPreviewZoomOutButton(const PrintPreviewZoomOutButton& source) {
}

PrintPreviewZoomOutButton::~PrintPreviewZoomOutButton() {
}

void PrintPreviewZoomOutButton::ButtonPress(PrintPreview *printPreview) {
	printPreview->zoomRate -= 10;
	if (printPreview->zoomRate < 50) {
		printPreview->zoomRate = 50;
	}
	printPreview->Invalidate();
}