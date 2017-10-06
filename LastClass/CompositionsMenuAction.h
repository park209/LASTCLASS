
#ifndef _COMPOSITIONSMENUACTION_H
#define _COMPOSITIONSMENUACTION_H
#include "MenuAction.h"

class CompositionsMenuAction : public MenuAction {
public:
	CompositionsMenuAction();
	virtual ~CompositionsMenuAction();
	void MenuPress(ClassDiagramForm *classDiagramForm);
};
#endif // !_COMPOSITIONSMENUACTION_H
