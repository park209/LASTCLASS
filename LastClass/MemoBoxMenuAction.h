#ifndef _MEMOBOXMENUACTION_H
#define _MEMOBOXMENUACTION_H

#include "MenuAction.h"

class MemoBoxMenuAction : public MenuAction {
public:
	MemoBoxMenuAction();
	virtual ~MemoBoxMenuAction();
	void MenuPress(ClassDiagramForm *classDiagramForm);
};
#endif // !_MEMOBOXMENUACTION_H
