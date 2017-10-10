#include "FilePrintPreviewMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "PrintPreview.h"
#include <afxwin.h>
#include <afxext.h>
using namespace std;
FilePrintPreviewMenuAction::FilePrintPreviewMenuAction() {
}
FilePrintPreviewMenuAction::~FilePrintPreviewMenuAction() {
}
void FilePrintPreviewMenuAction::MenuPress(LastClass* lastClass) {
	lastClass->classDiagramForm->selection->DeleteAllItems();
	 
	//CView *printView = NULL;
	//printView->Create(NULL, "#33", WS_VISIBLE, CRect(100, 100, 700, 700), lastClass, 9999);
	//CPrintPreviewState *pState = new CPrintPreviewState;
	lastClass->printPreview= new PrintPreview(lastClass);
	lastClass->printPreview->Create(NULL, "printPreview", WS_CHILD | WS_VISIBLE  , CRect(10,10,1200,900), lastClass,10001, NULL);
}