#include "MemoLineMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
MemoLineMenuAction::MemoLineMenuAction() {
}
MemoLineMenuAction::~MemoLineMenuAction() {
}
void MemoLineMenuAction::MenuPress(LastClass* lastClass) {
	lastClass->classDiagramForm->mouseLButton->ChangeDrawingMemoLineState();
}