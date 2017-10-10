//EditResizerBlocker.h

#ifndef _EDITRESIZERBLOCKER_H
#define _EDITRESIZERBLOCKER_H

#include <afxwin.h>

class TextEdit;
class EditResizerBlocker {
public:
	EditResizerBlocker();
	EditResizerBlocker(const EditResizerBlocker& source);
	~EditResizerBlocker();

	void Block(TextEdit *textEdit, CDC *pDC);
};

#endif // !_EDITRESIZERBLOCKER_H
