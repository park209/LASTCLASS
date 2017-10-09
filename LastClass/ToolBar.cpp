//ToolBar.cpp

#include "ToolBar.h"

ToolBar::ToolBar() {
}

ToolBar::~ToolBar() {
}

ToolBar::ToolBar(const ToolBar& source) {
}

void ToolBar::MakeToolBar(HWND hWndParent) {
	InitCommonControls();
	HWND hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | CCS_VERT | CCS_NORESIZE | WS_BORDER, 0, 0, 30, 1800,
		hWndParent, NULL, GetModuleHandle(NULL), NULL);
	SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	TBBUTTON tbb[5];
	TBADDBITMAP tbab;
	tbab.hInst = HINST_COMMCTRL;
	tbab.nID = IDB_STD_LARGE_COLOR;
	SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tbab);
	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = STD_FILENEW;
	tbb[0].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[0].idCommand = ID_FILE_NEW;

	tbb[1].iBitmap = STD_FILEOPEN;
	tbb[1].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[1].fsStyle = TBSTYLE_BUTTON;
	tbb[1].idCommand = ID_FILE_OPEN;

	tbb[2].iBitmap = STD_FILESAVE;
	tbb[2].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[2].fsStyle = TBSTYLE_BUTTON;
	tbb[2].idCommand = ID_FILE_SAVE;

	tbb[3].iBitmap = STD_UNDO;
	tbb[3].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[3].fsStyle = TBSTYLE_BUTTON;
	tbb[3].idCommand = ID_EDIT_UNDO;

	tbb[4].iBitmap = STD_REDOW;
	tbb[4].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[4].fsStyle = TBSTYLE_BUTTON;
	SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)tbb);
	//SetWindowPos(hTool, NULL, 0,100, 150,1800, SWP_NOZORDER);
	//SendMessage(hTool,TB_GETRECT,
}