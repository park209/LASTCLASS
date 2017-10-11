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
	 
	
	lastClass->printPreview= new PrintPreview(lastClass);
	lastClass->printPreview->Create(NULL, "printPreview");

	lastClass->printPreview->ShowWindow(SW_MAXIMIZE);

	lastClass->printPreview->UpdateWindow();


}