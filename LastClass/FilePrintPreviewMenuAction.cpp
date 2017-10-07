#include "FilePrintPreviewMenuAction.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "PrintPreview.h"
FilePrintPreviewMenuAction::FilePrintPreviewMenuAction() {
}
FilePrintPreviewMenuAction::~FilePrintPreviewMenuAction() {
}
void FilePrintPreviewMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	classDiagramForm->selection->DeleteAllItems();
	
	PrintPreview *printPreview = new PrintPreview(classDiagramForm);
	printPreview->Create(NULL, "printPreview", WS_CHILD | WS_VISIBLE|WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CRect(10,10,1200,900), classDiagramForm,10001,NULL);
	
}