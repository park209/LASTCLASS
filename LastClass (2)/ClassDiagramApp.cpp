#include "ClassDiagramForm.h"
#include "ClassDiagramApp.h"

BOOL ClassDiagramApp::InitInstance() {
	ClassDiagramForm *classDiagramForm = new ClassDiagramForm;

	classDiagramForm->Create(NULL, "classDiagram"); //CFrameWnd �� ���پ��µ�??
	//WS_VSCROLL
	classDiagramForm->ShowWindow(SW_SHOWMAXIMIZED);
	classDiagramForm->UpdateWindow();
	this->m_pMainWnd = classDiagramForm;

	return TRUE;
}

ClassDiagramApp classDiagramApp;
