//PrintPreviewZoomInButton.h

#ifndef _PRINTPREVIEWZOOMINBUTTON_H
#define _PRINTPREVIEWZOOMINBUTTON_H

#include "PrintPreviewButtonAction.h"

class PrintPreviewZoomInButton : public PrintPreviewButtonAction {
public:
	PrintPreviewZoomInButton();
	PrintPreviewZoomInButton(const PrintPreviewZoomInButton& source);
	virtual ~PrintPreviewZoomInButton();
public:
	void ButtonPress(PrintPreview *printPreview);
};

#endif // _PRINTPREVIEWZOOMINBUTTON_H