#include "OpenMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
#include "Diagram.h"
#include "Selection.h"
#include "HistoryGraphic.h"
#include "KeyBoard.h"
#include "ResizeVisitor.h"
#include "KnockKnock.h"
#include "ResizeVisitor.h"
#include "StatusBar.h"

#include <afxdlgs.h>
using namespace std;

OpenMenuAction::OpenMenuAction() {
}
OpenMenuAction::~OpenMenuAction() {
}
void OpenMenuAction::MenuPress(LastClass* lastClass) {

	int messageBox = IDNO;
	INT_PTR int_ptr = IDOK;
	if (lastClass->classDiagramForm->historyGraphic->undoGraphicArray->GetLength() != 0
		|| lastClass->classDiagramForm->historyGraphic->redoGraphicArray->GetLength() != 0) {
		if (lastClass->classDiagramForm->fileName == "") {
			messageBox = lastClass->MessageBox(_T("변경 내용을 제목 없음에 저장하시겠습니까?"), "ClassDiagram", MB_YESNOCANCEL);

			if (messageBox == IDYES) {
				CFileDialog  dlgFile(false, "txt", "*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT, "텍스트 문서(*.txt)");
				int_ptr = dlgFile.DoModal();
				if (int_ptr == IDOK) {
					ResizeVisitor resizeVisitor1(lastClass->classDiagramForm->zoomRate, 100);
					CDC dc;
					//lastClass->classDiagramForm->diagram->Accept(resizeVisitor1, &dc);
					
					lastClass->classDiagramForm->fileName = dlgFile.GetPathName();
					lastClass->classDiagramForm->Save();

					ResizeVisitor resizeVisitor2(100, lastClass->classDiagramForm->zoomRate);
					//lastClass->classDiagramForm->diagram->Accept(resizeVisitor2, &dc);
				}
			}
			else if (messageBox == IDCANCEL) {
				int_ptr = IDCANCEL;
			}
		}
		else {
			CString object;
			object = "변경내용을 ";
			object.Append(lastClass->classDiagramForm->fileName);
			object.Append("에 저장하시겠습니까?");
			messageBox = lastClass->MessageBox(object, "ClassDiagram", MB_YESNOCANCEL);
			if (messageBox == IDYES) {
				ResizeVisitor resizeVisitor1(lastClass->classDiagramForm->zoomRate, 100);
				CDC dc;
				//lastClass->classDiagramForm->diagram->Accept(resizeVisitor1, &dc);

				lastClass->classDiagramForm->Save();

				ResizeVisitor resizeVisitor2(100, lastClass->classDiagramForm->zoomRate);
				//lastClass->classDiagramForm->diagram->Accept(resizeVisitor2, &dc);
			}
			else if (messageBox == IDCANCEL) {
				int_ptr = IDCANCEL;
			}
		}
	}
	if (int_ptr != IDCANCEL) {
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
			lastClass->classDiagramForm->diagram = new Diagram();
			lastClass->classDiagramForm->selection = new Selection;
			lastClass->classDiagramForm->mouseLButton = new MouseLButton;
			lastClass->classDiagramForm->historyGraphic = new HistoryGraphic;
			lastClass->classDiagramForm->keyBoard = new KeyBoard;
			lastClass->classDiagramForm->fileName = dlgFile.GetPathName();
			lastClass->classDiagramForm->Load();

			lastClass->classDiagramForm->preZoom = 100;
			lastClass->classDiagramForm->SetMemoGab(20 * lastClass->classDiagramForm->zoomRate / 100);
			lastClass->classDiagramForm->SetGabX(8 * lastClass->classDiagramForm->zoomRate / 100);
			lastClass->classDiagramForm->SetGabY(2 * lastClass->classDiagramForm->zoomRate / 100);
			lastClass->classDiagramForm->SetCaretWidth(2 * lastClass->classDiagramForm->zoomRate / 100);

			ResizeVisitor visitor(lastClass->classDiagramForm->preZoom, lastClass->classDiagramForm->zoomRate);
			CDC dc;
		//	lastClass->classDiagramForm->diagram->Accept(visitor, &dc);

			KnockKnock *knocking = new KnockKnock;
			knocking->Knocking(lastClass->classDiagramForm);
			if (knocking != NULL) {
				delete knocking;
			}
			
			SCROLLINFO vScinfo;
			SCROLLINFO hScinfo;

			lastClass->classDiagramForm->GetScrollInfo(SB_VERT, &vScinfo);
			lastClass->classDiagramForm->GetScrollInfo(SB_HORZ, &hScinfo);
			CRect rect;
			lastClass->classDiagramForm->GetClientRect(&rect);
			vScinfo.nPage = rect.Height();
			hScinfo.nPage = rect.Width();

			vScinfo.nMax = 2000 * lastClass->classDiagramForm->zoomRate / 100;
			hScinfo.nMax = 4000 * lastClass->classDiagramForm->zoomRate / 100;

			
			lastClass->classDiagramForm->SetScrollInfo(SB_VERT, &vScinfo);
			lastClass->classDiagramForm->SetScrollInfo(SB_HORZ, &hScinfo);


			lastClass->statusBar->DestroyStatus();
			lastClass->statusBar->MakeStatusBar(lastClass, lastClass->GetSafeHwnd(), 0, 0, 5);
		}
	}
}