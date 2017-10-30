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
	void ResizeEditAll(TextEdit *textEdit, CDC *cdc);
	void RewindEdit(TextEdit *textEdit, CDC *cdc);

	void ResizeClassHeight(TextEdit *textEdit);

	void ResizeEditWidthToLeft(TextEdit *textEdit, CDC *cdc);
	void ResizeTemplateWidth(TextEdit *textEdit);

	void AffectedRelation(TextEdit *textEdit);
};

#endif // _EDITRESIZERPROCESS_H
