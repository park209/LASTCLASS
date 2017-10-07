#include "MemoLineMenuAction.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
MemoLineMenuAction::MemoLineMenuAction() {
}
MemoLineMenuAction::~MemoLineMenuAction() {
}
void MemoLineMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	classDiagramForm->mouseLButton->ChangeState(87);
}