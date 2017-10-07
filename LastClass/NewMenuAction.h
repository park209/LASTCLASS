#ifndef _NEWMENUACTION_H
#define _NEWMENUACTION_H

#include "MenuAction.h"

class NewMenuAction : public MenuAction {
public:
	NewMenuAction();
	virtual ~NewMenuAction();
	void MenuPress(ClassDiagramForm *classDiagramForm);
};
#endif // !_NEWMENUACTION_H
