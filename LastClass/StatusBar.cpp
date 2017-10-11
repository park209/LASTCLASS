
#include "StatusBar.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Diagram.h"

StatusBar::StatusBar() {
}

StatusBar::StatusBar(const StatusBar& source) {
}

StatusBar::~StatusBar() {
}

HWND StatusBar::MakeStatusBar(LastClass *lastClass, HWND hwndParent, int idStatus, HINSTANCE hinst, int cParts) {
	HWND hwndStatus;
	RECT rcClient;
	HLOCAL hloc;
	PINT paParts;
	int i, nWidth;

	// Ensure that the common control DLL is loaded.
	InitCommonControls();

	// Create the status bar.
	hwndStatus = CreateWindowEx(
		WS_EX_APPWINDOW  | WS_EX_WINDOWEDGE,   // no extended styles
		STATUSCLASSNAME,         // name of status bar class
		(PCTSTR)" Draw ClassDiagram!!!  Version 2.27              ParkCom 02)587-9424",           // no text when first created
		//SBARS_SIZEGRIP |         // includes a sizing grip
		WS_CHILD | WS_VISIBLE,   // creates a visible child window
		0, 0, 0, 0,              // ignores size and position
		hwndParent,              // handle to parent window
		(HMENU)idStatus,		 // child window identifier
		hinst,                   // handle to application instance
		NULL);                   // no window creation data

								 // Get the coordinates of the parent window's client area.
	lastClass->GetClientRect(&rcClient);

	// Allocate an array for holding the right edge coordinates.
	hloc = LocalAlloc(LHND, sizeof(int) * cParts - 10);
	paParts = (PINT)LocalLock(hloc);

	// Calculate the right edge coordinate for each part, and
	// copy the coordinates to the array.
	nWidth = rcClient.right / cParts;
	paParts[0] = nWidth * 3;
	int rightEdge = nWidth * 3 + nWidth/2;
	for (i = 1; i < cParts; i++) {
		paParts[i] = rightEdge;
		rightEdge += nWidth/2;
	}

	// Tell the status bar to create the window parts.
	//언제 lastClass , 다시 그리거나 각각 따로 다시 호출해주거나 할지 정해야함
	SendMessage(hwndStatus, SB_SETPARTS, (WPARAM)cParts, (LPARAM)paParts);
	if (lastClass->classDiagramForm->capsLockFlag == 0) {
		SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)1, (LPARAM)" CapsLock Off ");
	}
	else {
		SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)1, (LPARAM)" CapsLock On ");
	}
	if (lastClass->classDiagramForm->textEdit != 0 && lastClass->classDiagramForm->textEdit->numLockFlag == 1) {
		SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)2, (LPARAM)" NumLook On ");
	}
	else {
		SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)2, (LPARAM)" NumLook Off ");
	}

	Long tempLength = lastClass->classDiagramForm->diagram->GetLength();
	int a = tempLength;
	CString tempString;
	tempString.Format(" Obj : %d", tempLength);
	SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)3, (LPARAM)(LPCTSTR)tempString);

	SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)4, (LPARAM)"  ");
	// Free the array, and return.
	LocalUnlock(hloc);
	LocalFree(hloc);

	CRect rect;
	lastClass->GetClientRect(&rect);
	rect.top = rect.bottom - 30;
	rect.left += 50;
	lastClass->InvalidateRect(rect);
	//lastClass->Invalidate();

	return hwndStatus;
}