#include "MemoBoxMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
MemoBoxMenuAction::MemoBoxMenuAction() {
}
MemoBoxMenuAction::~MemoBoxMenuAction() {
}
void MemoBoxMenuAction::MenuPress(LastClass* lastClass) {
	lastClass->classDiagramForm->mouseLButton->ChangeDrawingMemoBoxState();
}