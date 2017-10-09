
#include "StatusBar.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"

StatusBar::StatusBar() {
}

StatusBar::StatusBar(const StatusBar& source) {
}

StatusBar::~StatusBar() {
}

HWND StatusBar::MakeStatusBar(LastClass *lastClass, HWND hwndParent, int idStatus, HINSTANCE hinst, int cParts) {
//HWND StatusBar::MakeStatusBar(ClassDiagramForm *classDiagramForm, HWND hwndParent, int idStatus, HINSTANCE hinst, int cParts) {
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
		(PCTSTR)"wow",           // no text when first created
		SBARS_SIZEGRIP |         // includes a sizing grip
		WS_CHILD | WS_VISIBLE,   // creates a visible child window
		0, 0, 0, 0,              // ignores size and position
		hwndParent,              // handle to parent window
		(HMENU)idStatus,       // child window identifier
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
	int rightEdge = nWidth;
	for (i = 0; i < cParts; i++) {
		paParts[i] = rightEdge;
		rightEdge += nWidth;
	}

	// Tell the status bar to create the window parts.
	SendMessage(hwndStatus, SB_SETPARTS, (WPARAM)cParts, (LPARAM)paParts);

	// Free the array, and return.
	LocalUnlock(hloc);
	LocalFree(hloc);
	return hwndStatus;
}