#include "SaveAsMenuAction.h"
#include "ClassDiagramForm.h"
#include <afxdlgs.h>
using namespace std;

SaveAsMenuAction::SaveAsMenuAction() {
}
SaveAsMenuAction::~SaveAsMenuAction() {
}
void SaveAsMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {

	CFileDialog  dlgFile(false,"txt","*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT,"텍스트 문서(*.txt)");
	if (dlgFile.DoModal() == IDOK)
	{
		classDiagramForm->fileName = dlgFile.GetPathName();
		classDiagramForm->Save();
	}

}