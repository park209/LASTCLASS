#include "MemoBoxMenuAction.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
MemoBoxMenuAction::MemoBoxMenuAction() {
}
MemoBoxMenuAction::~MemoBoxMenuAction() {
}
void MemoBoxMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	classDiagramForm->mouseLButton->ChangeState(81);
}