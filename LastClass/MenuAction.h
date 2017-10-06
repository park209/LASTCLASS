#ifndef _MENUACTIOIN_H
#define _MENUACTIOIN_H
class ClassDiagramForm;
class MenuAction {
public:
	MenuAction() {};
	virtual ~MenuAction() = 0 {};
	virtual void MenuPress(ClassDiagramForm *classDiagramForm) = 0;
};
#endif // !_MENUACTIOIN_H
