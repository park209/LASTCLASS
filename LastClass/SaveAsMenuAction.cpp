#include "SaveAsMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include <afxdlgs.h>
using namespace std;

SaveAsMenuAction::SaveAsMenuAction() {
}
SaveAsMenuAction::~SaveAsMenuAction() {
}
void SaveAsMenuAction::MenuPress(LastClass* lastClass) {

	CFileDialog  dlgFile(false,"txt","*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT,"텍스트 문서(*.txt)");
	if (dlgFile.DoModal() == IDOK)
	{
		lastClass->classDiagramForm->fileName = dlgFile.GetPathName();
		lastClass->classDiagramForm->Save();
	}

}