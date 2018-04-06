//PrintPreviewZoomOutButton.h

#ifndef _PRINTPREVIEWZOOMOUTBUTTON_H
#define _PRINTPREVIEWZOOMOUTBUTTON_H

#include "PrintPreviewButtonAction.h"

class PrintPreviewZoomOutButton : public PrintPreviewButtonAction {
public:
	PrintPreviewZoomOutButton();
	PrintPreviewZoomOutButton(const PrintPreviewZoomOutButton& source);
	virtual ~PrintPreviewZoomOutButton();
public:
	void ButtonPress(PrintPreview *printPreview);
};

#endif // _PRINTPREVIEWZOOMOUTBUTTON_H