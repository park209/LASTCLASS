#include "LastClass.h"
#include "ClassDiagramApp.h"

BOOL ClassDiagramApp::InitInstance() {
	LastClass *lastClass = new LastClass;

	lastClass->Create(NULL, "LastClass"); //CFrameWnd �� ���پ��µ�??
	lastClass->ShowWindow(SW_SHOW);
	lastClass->UpdateWindow();
	this->m_pMainWnd = lastClass;

	return TRUE;
}

ClassDiagramApp classDiagramApp;