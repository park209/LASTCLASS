
#ifndef _AGGREGATIONMENUACTION_H
#define _AGGREGATIONMENUACTION_H
#include "MenuAction.h"

class AggregationMenuAction : public MenuAction {
public:
	AggregationMenuAction();
	virtual ~AggregationMenuAction();
	void MenuPress(ClassDiagramForm *classDiagramForm);
};
#endif // !_AGGREGATIONMENUACTION_H
