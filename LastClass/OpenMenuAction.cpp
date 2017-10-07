#include "OpenMenuAction.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
#include <afxdlgs.h>
using namespace std;

OpenMenuAction::OpenMenuAction() {
}
OpenMenuAction::~OpenMenuAction() {
}
void OpenMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	CFileDialog  dlgFile(true, "txt", "*", NULL, "텍스트 문서(*.txt)");
	if (dlgFile.DoModal() == IDOK)
	{
		classDiagramForm->fileName = dlgFile.GetPathName();
		classDiagramForm->Load();
	}
}