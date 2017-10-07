
#ifndef _ASSOCIATIONMENUACTION_H	
#define _ASSOCIATIONMENUACTION_H
#include "MenuAction.h"

class AssociationMenuAction : public MenuAction {
public:
	AssociationMenuAction();
	virtual ~AssociationMenuAction();
	void MenuPress(ClassDiagramForm *classDiagramForm);
};
#endif // !_ASSOCIATIONMENUACTION_H
