#include "ToolBar.h"
ToolBar::ToolBar() {
}
ToolBar::ToolBar(const ToolBar& source) {
}
ToolBar::~ToolBar() {
}
void ToolBar::MakeToolBar(HWND hWndParent) {
	InitCommonControls();
	HWND hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | CCS_NORESIZE | WS_BORDER, 0, 0, 1361, 45,
		hWndParent, NULL, GetModuleHandle(NULL), NULL);
	SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	TBBUTTON tbb[12];
	TBADDBITMAP tbab;
	Long iNew, iopen, iSave, iredo, iundo, idelete_, icut, icopy, ipaste, iprint, iprintpre, ihelp;
	TCHAR newfile[10] = "새파일";
	TCHAR open[10] = "열기";
	TCHAR save[10] = "저장하기";
	TCHAR redo[10] = "다시 실행";
	TCHAR undo[10] = "실행 취소";
	TCHAR delete_[10] = "지우기";
	TCHAR cut[10] = "자르기";
	TCHAR copy[10] = "복사하기";
	TCHAR paste[10] = "복사하기";
	TCHAR print[10] = "인쇄하기";
	TCHAR printpre[10] = "미리보기";
	TCHAR help[10] = "도움말";

	tbab.hInst = HINST_COMMCTRL;
	tbab.nID = IDB_STD_SMALL_COLOR;
	SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tbab);
	iNew = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)newfile);
	iopen = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)open);
	iSave = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)save);
	iredo = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)redo);
	iundo = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)undo);
	idelete_ = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)delete_);
	icut = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)cut);
	icopy = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)copy);
	ipaste = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)paste);
	iprint = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)print);
	iprintpre = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)printpre);
	ihelp = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)help);
	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = STD_FILENEW;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[0].idCommand = ID_FILE_NEW;
	tbb[0].iString = iNew;

	tbb[1].iBitmap = STD_FILEOPEN;
	tbb[1].fsState = TBSTATE_ENABLED;
	tbb[1].fsStyle = TBSTYLE_BUTTON;
	tbb[1].idCommand = ID_FILE_OPEN;
	tbb[1].iString = iopen;

	tbb[2].iBitmap = STD_FILESAVE;
	tbb[2].fsState = TBSTATE_ENABLED;
	tbb[2].fsStyle = TBSTYLE_BUTTON;
	tbb[2].idCommand = ID_FILE_SAVE;
	tbb[2].iString = iSave;

	tbb[3].iBitmap = STD_UNDO;
	tbb[3].fsState = TBSTATE_ENABLED;
	tbb[3].fsStyle = TBSTYLE_BUTTON;
	tbb[3].idCommand = ID_EDIT_UNDO;
	tbb[3].iString = iundo;

	tbb[4].iBitmap = STD_REDOW;
	tbb[4].fsState = TBSTATE_ENABLED;
	tbb[4].fsStyle = TBSTYLE_BUTTON;
	tbb[4].idCommand = ID_EDIT_REDO;
	tbb[4].iString = iredo;

	tbb[5].iBitmap = STD_DELETE;
	tbb[5].fsState = TBSTATE_ENABLED;
	tbb[5].fsStyle = TBSTYLE_BUTTON;
	tbb[5].idCommand = ID_EDIT_CLEAR;
	tbb[5].iString = idelete_;

	tbb[6].iBitmap = STD_CUT;
	tbb[6].fsState = TBSTATE_ENABLED;
	tbb[6].fsStyle = TBSTYLE_BUTTON;
	tbb[6].idCommand = ID_EDIT_CUT;
	tbb[6].iString = icut;

	tbb[7].iBitmap = STD_COPY;
	tbb[7].fsState = TBSTATE_ENABLED;
	tbb[7].fsStyle = TBSTYLE_BUTTON;
	tbb[7].idCommand = ID_EDIT_COPY;
	tbb[7].iString = icopy;

	tbb[8].iBitmap = STD_PASTE;
	tbb[8].fsState = TBSTATE_ENABLED;
	tbb[8].fsStyle = TBSTYLE_BUTTON;
	tbb[8].idCommand = ID_EDIT_PASTE;
	tbb[8].iString = ipaste;

	tbb[9].iBitmap = STD_PRINT;
	tbb[9].fsState = TBSTATE_ENABLED;
	tbb[9].fsStyle = TBSTYLE_BUTTON;
	tbb[9].idCommand = ID_FILE_PRINT;
	tbb[9].iString = iprint;

	tbb[10].iBitmap = STD_PRINTPRE;
	tbb[10].fsState = TBSTATE_ENABLED;
	tbb[10].fsStyle = TBSTYLE_BUTTON;
	tbb[10].idCommand = ID_FILE_PRINT_PREVIEW;
	tbb[10].iString = iprintpre;

	tbb[11].iBitmap = STD_HELP;
	tbb[11].fsState = TBSTATE_ENABLED;
	tbb[11].fsStyle = TBSTYLE_BUTTON;
	tbb[11].idCommand = ID_CONTEXT_HELP;
	tbb[11].iString = ihelp;

	SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)tbb);

}
void ToolBar::MakeAnotherToolBar(HWND hWndParent) {
	InitCommonControls();
	HWND hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | CCS_VERT | CCS_NORESIZE | WS_BORDER, 0, 46, 60, 634,
		hWndParent, NULL, GetModuleHandle(NULL), NULL);
	SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	TBBUTTON tbb[5];
	Long iClass;
	TCHAR class_[10] = "CLASS";
	//TBADDBITMAP tbab;
	/*CImageList *pImageList = new CImageList;
	CBitmap bitmap;
	pImageList->Create(30, 30, ILC_COLORDDB | ILC_MASK, 25, 0);
	bitmap.LoadBitmap(IDB_BITMAP1);*/
	//COLORSCHEME color{ 30,RGB(0,0,0),RGB(0,0,0) };
	//SendMessage(hTool, TB_SETCOLORSCHEME, 0, (LPARAM)&color);
	SendMessage(hTool, TB_SETBUTTONSIZE, 0, MAKELPARAM(58, 47));

	COLORMAP colorMap;
	colorMap.from = RGB(0, 0, 0);
	colorMap.to = RGB(0,0,0);
	//HBITMAP hbm = CreateMappedBitmap(NULL, IDB_BITMAP1, 0, &colorMap, 1);
	SendMessage(hTool, TB_SETBITMAPSIZE, 0,(LPARAM) MAKELPARAM(48, 47));
	TBADDBITMAP tb;
	tb.hInst = NULL;
	//tb.nID = (UINT_PTR)hbm;

	// hWndToolbar is the window handle of the toolbar.
	// Do not forget to send TB_BUTTONSTRUCTSIZE if the toolbar was 
	// created by using CreateWindowEx.
	int index = SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tb);
	iClass = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)class_);
	/*tbab.hInst = HINST_COMMCTRL;
	tbab.nID = IDB_STD_LARGE_COLOR;
	SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tbab);
	
*/
	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = index;
	tbb[0].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[0].fsStyle = TBSTYLE_BUTTON ;
	//tbb[0].idCommand = ID_
	tbb[0].iString = iClass;

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
	tbb[4].idCommand = ID_EDIT_REDO;
	SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)tbb);
}
