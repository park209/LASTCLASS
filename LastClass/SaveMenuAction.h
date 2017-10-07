#ifndef _SAVEMENUACTION_H
#define _SAVEMENUACTION_H

#include "MenuAction.h"

class SaveMenuAction : public MenuAction {
public:
	SaveMenuAction();
	virtual ~SaveMenuAction();
	void MenuPress(ClassDiagramForm *classDiagramForm);
};
#endif // !_SAVEMENUACTION_H
