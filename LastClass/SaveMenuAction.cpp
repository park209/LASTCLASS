#include "SaveMenuAction.h"
#include "ClassDiagramForm.h"
#include <afxdlgs.h>
using namespace std;
SaveMenuAction::SaveMenuAction() {
}
SaveMenuAction::~SaveMenuAction() {
}
void SaveMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	if (classDiagramForm->fileName == "") {
		int messageBox = classDiagramForm->MessageBox(_T("변경 내용을 제목 없음에 저장하시겠습니까?"), "ClassDiagram", MB_YESNOCANCEL);
		if (messageBox == IDYES) {
			CFileDialog  dlgFile(false, "txt", "*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT, "텍스트 문서(*.txt)");
			if (dlgFile.DoModal() == IDOK){
				classDiagramForm->fileName = dlgFile.GetPathName();
				classDiagramForm->Save();
			}
		}
	}
		

}