//ToolBar.cpp

#include "ToolBar.h"
#include "resource.h"
#include "ToolBarProcess.h"

ToolBar::ToolBar() {
	this->hTool1 = 0;
	this->hTool2 = 0;
}
ToolBar::ToolBar(const ToolBar& source) {
}
ToolBar::~ToolBar() {
}
void ToolBar::MakeToolBar(HWND hWndParent) {
	InitCommonControls();
	HWND hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | CCS_NORESIZE | WS_BORDER, 0, 0, 1361, 45,
		hWndParent, NULL, GetModuleHandle(NULL), NULL);
	this->hTool1 = hTool;
	SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	TBBUTTON tbb[12];
	TBADDBITMAP tbab;
	Long iNew, iopen, iSave, iredo, iundo, idelete_, icut, icopy, ipaste, iprint, iprintpre, ihelp;
	TCHAR newfile[10] = "새파일";
	TCHAR open[10] = "열기";
	TCHAR save[10] = "저장하기";
	TCHAR redo[10] = "재실행";
	TCHAR undo[10] = "되돌리기";
	TCHAR delete_[10] = "지우기";
	TCHAR cut[10] = "자르기";
	TCHAR copy[10] = "복사하기";
	TCHAR paste[10] = "붙여넣기";
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
	tbb[0].idCommand = ID_BUTTON40001;
	tbb[0].iString = iNew;

	tbb[1].iBitmap = STD_FILEOPEN;
	tbb[1].fsState = TBSTATE_ENABLED;
	tbb[1].fsStyle = TBSTYLE_BUTTON;
	tbb[1].idCommand = ID_BUTTON40002;
	tbb[1].iString = iopen;

	tbb[2].iBitmap = STD_FILESAVE;
	tbb[2].fsState = TBSTATE_ENABLED;
	tbb[2].fsStyle = TBSTYLE_BUTTON;
	tbb[2].idCommand = ID_BUTTON40003;
	tbb[2].iString = iSave;

	tbb[3].iBitmap = STD_UNDO;
	tbb[3].fsState = TBSTATE_ENABLED;
	tbb[3].fsStyle = TBSTYLE_BUTTON;
	tbb[3].idCommand = ID_BUTTON40005;
	tbb[3].iString = iundo;

	tbb[4].iBitmap = STD_REDOW;
	tbb[4].fsState = TBSTATE_ENABLED;
	tbb[4].fsStyle = TBSTYLE_BUTTON;
	tbb[4].idCommand = ID_BUTTON40006;
	tbb[4].iString = iredo;

	tbb[8].iBitmap = STD_DELETE;
	tbb[8].fsState = TBSTATE_ENABLED;
	tbb[8].fsStyle = TBSTYLE_BUTTON;
	tbb[8].idCommand = ID_BUTTON40007;
	tbb[8].iString = idelete_;

	tbb[5].iBitmap = STD_CUT;
	tbb[5].fsState = TBSTATE_ENABLED;
	tbb[5].fsStyle = TBSTYLE_BUTTON;
	tbb[5].idCommand = ID_BUTTON40008;
	tbb[5].iString = icut;

	tbb[6].iBitmap = STD_COPY;
	tbb[6].fsState = TBSTATE_ENABLED;
	tbb[6].fsStyle = TBSTYLE_BUTTON;
	tbb[6].idCommand = ID_BUTTON40009;
	tbb[6].iString = icopy;

	tbb[7].iBitmap = STD_PASTE;
	tbb[7].fsState = TBSTATE_ENABLED;
	tbb[7].fsStyle = TBSTYLE_BUTTON;
	tbb[7].idCommand = ID_BUTTON40010;
	tbb[7].iString = ipaste;

	tbb[9].iBitmap = STD_PRINT;
	tbb[9].fsState = TBSTATE_ENABLED;
	tbb[9].fsStyle = TBSTYLE_BUTTON;
	tbb[9].idCommand = ID_BUTTON40011;
	tbb[9].iString = iprint;

	tbb[10].iBitmap = STD_PRINTPRE;
	tbb[10].fsState = TBSTATE_ENABLED;
	tbb[10].fsStyle = TBSTYLE_BUTTON;
	tbb[10].idCommand = ID_BUTTON40012;
	tbb[10].iString = iprintpre;

	tbb[11].iBitmap = STD_HELP;
	tbb[11].fsState = TBSTATE_ENABLED;
	tbb[11].fsStyle = TBSTYLE_BUTTON;
	tbb[11].idCommand = ID_BUTTON40013;
	tbb[11].iString = ihelp;

	SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)tbb);
}
void ToolBar::MakeAnotherToolBar(HWND hWndParent) {
	InitCommonControls();
	HWND hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | CCS_VERT | CCS_NORESIZE | WS_BORDER, 0, 45, 60, 614,
		hWndParent, NULL, GetModuleHandle(NULL), NULL);
	this->hTool2 = hTool;
	SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	TBBUTTON tbb[5];
	SendMessage(hTool, TB_SETBUTTONSIZE, 0, MAKELPARAM(58, 47));
	SendMessage(hTool, TB_SETBITMAPSIZE, 0, (LPARAM)MAKELPARAM(50, 44));
	DWORD backgroundColor = GetSysColor(COLOR_BTNFACE);///여기부터
	COLORMAP colorMap;
	colorMap.from = RGB(0, 0, 0);
	colorMap.to = backgroundColor;
	//HBITMAP hbm = CreateMappedBitmap(NULL, IDB_BITMAP2, 0, &colorMap, 1);
	/*BITMAP bitInfo;
	CBitmap bmp;
	bmp.LoadBitmapA(IDB_BITMAP2);
	bmp.GetBitmap(&bitInfo);
	HBITMAP hbm = bmp.operator HBITMAP(); */
	TBADDBITMAP tb;
	tb.hInst = NULL;
	//tb.nID = (UINT_PTR)hbm;
	int index = SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tb);
	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = index;
	tbb[0].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[0].fsStyle = TBSTYLE_BUTTON ;
	tbb[0].idCommand = ID_BUTTON40001;

	SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)tbb);
}

void ToolBar::ButtonSelected(UINT parm_control_id, LastClass *lastClass, ClassDiagramForm *classDiagramForm, CDC *cdc) {
	ToolBarProcess toolBarProcess;
	switch (parm_control_id) {
	case  40002:toolBarProcess.OnOpenClicked(lastClass);
		break;
	case 40003:toolBarProcess.OnSaveFileClicked(lastClass);
		break;
	case 40004:toolBarProcess.OnNewFileClicked(lastClass);
		break;
	case 40005:toolBarProcess.OnUndoFileClicked(lastClass);
		break;
	case 40006:toolBarProcess.OnRedoFileClicked(lastClass);
		break;
	case 40007:
		break;
	case 40008:toolBarProcess.OnCutFileClicked(classDiagramForm, cdc);
		break;
	case 40009:toolBarProcess.OnCopyFileClicked(classDiagramForm, cdc);
		break;
	case 40010:toolBarProcess.OnPasteFileClicked(classDiagramForm, cdc);
		break;
	case 40011:
		break;		
	case 40012:toolBarProcess.OnPrintPreFileClicked(lastClass);
		break;
	case 40013:toolBarProcess.OnSupportFileClicked(lastClass);
		break;
	default:
		break;
	}
}

void ToolBar::ChangeToolBarSize(RECT *rect) {
	CWnd *cwnd= CWnd::FromHandle(this->hTool1);
	cwnd->SetWindowPos(cwnd, 0, 0, rect->right - 1, 45, SWP_NOMOVE | SWP_NOZORDER);
}
void ToolBar::ChangeAnotherToolBarSize(RECT *rect) {

}