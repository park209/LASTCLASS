//ToolBar.h

#ifndef _TOOLBAR_H
#define _TOOLBAR_H

#include <afxwin.h>
typedef signed long int  Long;
class ToolBar {
public:
	ToolBar();
	ToolBar(const ToolBar& source);
	 ~ToolBar();
	void MakeToolBar(HWND hWndParent);
	void MakeAnotherToolBar(HWND hWndParent);
};

#endif // _SPACEKEY_H
