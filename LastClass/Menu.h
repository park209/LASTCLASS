#ifndef _MENU_H
#define _MENU_H
#include <afxwin.h>
using namespace std;
class ClassDiagramForm;
class MenuAction;
class Menu {
public:
	Menu(ClassDiagramForm *classDiagramForm);
	~Menu();
	Menu(const Menu& source);
	MenuAction* MenuSelected( UINT parm_control_id);
	Menu& operator= (const Menu& source);

private:
	CMenu *mainMenu;
	CMenu *popupMenu;
	CMenu *editMenu;
	CMenu *drawMenu;
	CMenu *supportMenu;
	CMenu *relationMenu;
public:
	MenuAction *menuAction;
};
#endif // !_MENU_H
