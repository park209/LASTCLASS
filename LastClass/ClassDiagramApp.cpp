#include "ClassDiagramForm.h"
#include "ClassDiagramApp.h"

BOOL ClassDiagramApp::InitInstance() {
	ClassDiagramForm *classDiagramForm = new ClassDiagramForm;

	classDiagramForm->Create(NULL, "classDiagram"); //CFrameWnd 꺼 갖다쓰는듯??
	//WS_VSCROLL
	//classDiagramForm->ShowWindow(SW_SHOWMAXIMIZED);
	classDiagramForm->ShowWindow(SW_SHOW);
	classDiagramForm->UpdateWindow();
	this->m_pMainWnd = classDiagramForm;

	return TRUE;
}

ClassDiagramApp classDiagramApp;