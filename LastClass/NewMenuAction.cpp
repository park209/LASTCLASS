#include "NewMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
#include "Diagram.h"
#include "Selection.h"
#include "HistoryGraphic.h"
#include "KeyBoard.h"
#include "ResizeVisitor.h"
#include "StatusBar.h"

#include <afxdlgs.h>

using namespace std;

NewMenuAction::NewMenuAction() {
}
NewMenuAction::~NewMenuAction() {
}
void NewMenuAction::MenuPress(LastClass* lastClass) {
	int messageBox = IDNO;
	if (lastClass->classDiagramForm->historyGraphic->undoGraphicArray->GetLength() != 0
		|| lastClass->classDiagramForm->historyGraphic->redoGraphicArray->GetLength() != 0) {
		if (lastClass->classDiagramForm->fileName != "") { //저장된 이름이 있으면
			CString object;
			object = "변경내용을 ";
			object.Append(lastClass->classDiagramForm->fileName);
			object.Append("에 저장하시겠습니까?");
			messageBox = lastClass->classDiagramForm->MessageBox(object, "ClassDiagram", MB_YESNOCANCEL);
		}
		else { // 이름 없는 파일이면
			messageBox = lastClass->classDiagramForm->MessageBox(_T("변경 내용을 제목 없음에 저장하시겠습니까?"), "ClassDiagram", MB_YESNOCANCEL);
			if (messageBox == IDYES) {
				CFileDialog  dlgFile(false, "txt", "*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT, "텍스트 문서(*.txt)");
				if (dlgFile.DoModal() == IDOK)
				{
					lastClass->classDiagramForm->fileName = dlgFile.GetPathName();
				}
			}
		}
		if (messageBox == IDYES) {
			ResizeVisitor resizeVisitor1(lastClass->classDiagramForm->zoomRate, 100);
			CDC dc;
			lastClass->classDiagramForm->diagram->Accept(resizeVisitor1, &dc);

			lastClass->classDiagramForm->Save();
		}
	}
	if (messageBox != IDCANCEL) {
		lastClass->classDiagramForm->zoomRate = 100;

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
		//}
		lastClass->classDiagramForm->diagram = new Diagram();
		lastClass->classDiagramForm->selection = new Selection;
		lastClass->classDiagramForm->mouseLButton = new MouseLButton;
		lastClass->classDiagramForm->historyGraphic = new HistoryGraphic;
		//lastClass->classDiagramForm->verticalScrollBar = new VerticalScrollBar(lastClass->classDiagramForm);
		//lastClass->classDiagramForm->horizontalScroll = new HorizontalScrollBar(lastClass->classDiagramForm);
		lastClass->classDiagramForm->keyBoard = new KeyBoard;
		lastClass->classDiagramForm->fileName = "";
	}
	lastClass->statusBar->DestroyStatus();
	lastClass->statusBar->MakeStatusBar(lastClass, lastClass->GetSafeHwnd(), 0, 0, 5);

	lastClass->classDiagramForm->Invalidate(false);
}