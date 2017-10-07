#ifndef _CLASSMENUACTION_H
#define _CLASSMENUACTION_H

#include "MenuAction.h"

class ClassMenuAction : public MenuAction {
public:
	ClassMenuAction();
	virtual ~ClassMenuAction();
	void MenuPress(ClassDiagramForm *classDiagramForm);
};
#endif // !_CLASSMENUACTION_H
