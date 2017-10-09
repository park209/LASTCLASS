//StatusBar.h

#ifndef _STATUSBAR_H
#define _STATUSBAR_H

#include <afxext.h>

class LastClass;
class ClassDiagramForm;
class StatusBar {
public:
	StatusBar();
	StatusBar(const StatusBar& source);
	~StatusBar();
public:
	HWND MakeStatusBar(ClassDiagramForm *classDiagramForm, HWND hwndParent, int idStatus, HINSTANCE hinst, int cParts);
	HWND MakeStatusBar(LastClass *lastClass, HWND hwndParent, int idStatus, HINSTANCE hinst, int cParts);
};

#endif // _STATUSBAR_H
