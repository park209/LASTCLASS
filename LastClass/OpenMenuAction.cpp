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
			messageBox = lastClass->MessageBox(_T("���� ������ ���� ������ �����Ͻðڽ��ϱ�?"), "ClassDiagram", MB_YESNOCANCEL);

			if (messageBox == IDYES) {
				CFileDialog  dlgFile(false, "txt", "*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT, "�ؽ�Ʈ ����(*.txt)");
				int_ptr = dlgFile.DoModal();
				if (int_ptr == IDOK) {
					lastClass->classDiagramForm->fileName = dlgFile.GetPathName();
					lastClass->classDiagramForm->Save();
				}
			}
			else if (messageBox == IDCANCEL) {
				int_ptr = IDCANCEL;
			}
		}
		else {
			CString object;
			object = "���泻���� ";
			object.Append(lastClass->classDiagramForm->fileName);
			object.Append("�� �����Ͻðڽ��ϱ�?");
			messageBox = lastClass->MessageBox(object, "ClassDiagram", MB_YESNOCANCEL);
			if (messageBox == IDYES) {
				lastClass->classDiagramForm->Save();
			}
			else if (messageBox == IDCANCEL) {
				int_ptr = IDCANCEL;
			}
		}
	}
	if (int_ptr != IDCANCEL) {
		CFileDialog  dlgFile(true, "txt", "*.txt", NULL, "�ؽ�Ʈ ����(*.txt)");
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
			lastClass->classDiagramForm->selection = new Selection();
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

			KnockKnock *knocking = new KnockKnock;
		//	knocking->Knocking(lastClass->classDiagramForm);
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



			lastClass->classDiagramForm->SetScrollInfo(SB_VERT, &vScinfo);
			lastClass->classDiagramForm->SetScrollInfo(SB_HORZ, &hScinfo);


			lastClass->statusBar->DestroyStatus();
			lastClass->statusBar->MakeStatusBar(lastClass, lastClass->GetSafeHwnd(), 0, 0, 5);
		}
	}
}