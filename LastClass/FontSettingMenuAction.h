
#ifndef _FONTSETTINGMENUACTION_H
#define _FONTSETTINGMENUACTION_H
#include "MenuAction.h"

class FontSettingMenuaction : public MenuAction {
public:
	FontSettingMenuaction();
	virtual ~FontSettingMenuaction();
	void MenuPress(LastClass* lastClass);
};
#endif // !_FONTSETTINGMENUACTION_H
