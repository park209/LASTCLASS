#include "CompositionMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
CompositionMenuAction::CompositionMenuAction() {
}
CompositionMenuAction::~CompositionMenuAction() {
}
void CompositionMenuAction::MenuPress(LastClass* lastClass) {
	lastClass->classDiagramForm->mouseLButton->ChangeDrawingCompositionState();
}