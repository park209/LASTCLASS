#ifndef _DEPENDENCYMENUACTION_H	
#define _DEPENDENCYMENUACTION_H
#include "MenuAction.h"

class DependencyMenuAction : public MenuAction {
public:
	DependencyMenuAction();
	virtual ~DependencyMenuAction();
	void MenuPress(ClassDiagramForm *classDiagramForm);
};
#endif // !_DEPENDENCYMENUACTION_H
