#include "SaveAsMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"

#include "ResizeVisitor.h"
#include "Diagram.h"

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
		ResizeVisitor resizeVisitor1(lastClass->classDiagramForm->zoomRate, 100);
		CDC dc;
		lastClass->classDiagramForm->diagram->Accept(resizeVisitor1, &dc);

		lastClass->classDiagramForm->fileName = dlgFile.GetPathName();
		lastClass->classDiagramForm->Save();

		ResizeVisitor resizeVisitor2(100, lastClass->classDiagramForm->zoomRate);
		lastClass->classDiagramForm->diagram->Accept(resizeVisitor2, &dc);
	}

}