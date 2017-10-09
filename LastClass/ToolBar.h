//ToolBar.h

#ifndef _TOOLBAR_H
#define _TOOLBAR_H

#include <afxwin.h>

using namespace std;
typedef signed long int Long;
class ToolBar {
public:
	ToolBar();
	~ToolBar();
	ToolBar(const ToolBar& source);
	//ToolBar& operator= (const ToolBar& source);
public:
	void MakeToolBar(HWND hWndParent);
};

#endif // !_MENU_H