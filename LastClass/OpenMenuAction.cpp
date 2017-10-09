#include "OpenMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
#include "Diagram.h"
#include "Selection.h"
#include "HistoryGraphic.h"
#include "KeyBoard.h"

#include <afxdlgs.h>
using namespace std;

OpenMenuAction::OpenMenuAction() {
}
OpenMenuAction::~OpenMenuAction() {
}
void OpenMenuAction::MenuPress(LastClass* lastClass) {
	CFileDialog  dlgFile(true, "txt", "*.txt", NULL, "텍스트 문서(*.txt)");
	if (dlgFile.DoModal() == IDOK)
	{	
		if (lastClass->classDiagramForm->diagram != NULL) {
			delete lastClass->classDiagramForm->diagram;
		}
		if (lastClass->classDiagramForm->selection != NULL) {
			delete lastClass->classDiagramForm->selection;
		}
		if (lastClass->classDiagramForm->mouseLButton != NULL) {
			delete lastClass->classDiagramForm->mouseLButton;
		}
		if (lastClass->classDiagramForm->keyBoard != NULL) {
			delete lastClass->classDiagramForm->keyBoard;
		}
		if (lastClass->classDiagramForm->historyGraphic != NULL) {
			delete lastClass->classDiagramForm->historyGraphic;
		}
		//if (lastClass->classDiagramForm->verticalScrollBar != NULL) {
			//delete lastClass->classDiagramForm->verticalScrollBar;
		//}
		//if (lastClass->classDiagramForm->horizontalScroll != NULL) {
			//delete lastClass->classDiagramForm->horizontalScroll;
	//	}
		lastClass->classDiagramForm->diagram = new Diagram();
		lastClass->classDiagramForm->selection = new Selection;
		lastClass->classDiagramForm->mouseLButton = new MouseLButton;
		lastClass->classDiagramForm->historyGraphic = new HistoryGraphic;
		//lastClass->classDiagramForm->verticalScrollBar = new VerticalScrollBar(lastClass->classDiagramForm);
		//lastClass->classDiagramForm->horizontalScroll = new HorizontalScrollBar(lastClass->classDiagramForm);
		lastClass->classDiagramForm->keyBoard = new KeyBoard;
		lastClass->classDiagramForm->fileName = dlgFile.GetPathName();
		lastClass->classDiagramForm->Load();
	}
}