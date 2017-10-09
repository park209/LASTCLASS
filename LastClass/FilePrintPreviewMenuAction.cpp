#include "FilePrintPreviewMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "PrintPreview.h"
FilePrintPreviewMenuAction::FilePrintPreviewMenuAction() {
}
FilePrintPreviewMenuAction::~FilePrintPreviewMenuAction() {
}
void FilePrintPreviewMenuAction::MenuPress(LastClass* lastClass) {
	lastClass->classDiagramForm->selection->DeleteAllItems();
	
	PrintPreview *printPreview = new PrintPreview(lastClass);
	printPreview->Create(NULL, "printPreview", WS_CHILD | WS_VISIBLE|WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CRect(10,10,1200,900), lastClass,10001,NULL);

}