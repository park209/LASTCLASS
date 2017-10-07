
#ifndef _DIRECTEDASSOCIATIONMENUACTION_H	
#define _DIRECTEDASSOCIATIONMENUACTION_H
#include "MenuAction.h"

class DirectedAssociationMenuAction : public MenuAction {
public:
	DirectedAssociationMenuAction();
	virtual ~DirectedAssociationMenuAction();
	void MenuPress(ClassDiagramForm *classDiagramForm);
};
#endif // !_DIRECTEDASSOCIATIONMENUACTION_H
