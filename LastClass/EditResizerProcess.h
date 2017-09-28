//EditResizerProcess.h

#ifndef _EDITRESIZERPROCESS_H
#define _EDITRESIZERPROCESS_H

#include <afxwin.h>

class TextEdit;
class EditResizerProcess {
public:
	EditResizerProcess();
	EditResizerProcess(const EditResizerProcess& source);
	~EditResizerProcess();
public:
	void ResizeEditWidth(TextEdit *textEdit, CDC *cdc);
	void ResizeEditHeight(TextEdit *textEdit, CDC *cdc);
	void ResizeEditAll(TextEdit *textEdit, CDC *cdc);
	void RewindEdit(TextEdit *textEdit, CDC *cdc);

	void ResizeClassWidth(TextEdit *textEdit, CDC *cdc);
	void ResizeClassHeight(TextEdit *textEdit);
};

#endif // _EDITRESIZERPROCESS_H
