#ifndef _GENERALIZATIONMENUACTION_H
#define _GENERALIZATIONMENUACTION_H

#include "MenuAction.h"

class GeneralizationMenuAction : public MenuAction {
public:
	GeneralizationMenuAction();
	virtual ~GeneralizationMenuAction();
	void MenuPress(ClassDiagramForm *classDiagramForm);
};
#endif // !_GENERALIZATIONMENUACTION_H
