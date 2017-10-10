//ToolBar.h

#ifndef _TOOLBAR_H
#define _TOOLBAR_H

#include <afxwin.h>

class ToolBar {
public:
	ToolBar();
	ToolBar(const ToolBar& source);
	 ~ToolBar();
	HWND MakeToolBar(HWND hWndParent);
	HWND MakeAnotherToolBar(HWND hWndParent);
private:
	HWND hTool;
};

#endif // _SPACEKEY_H
