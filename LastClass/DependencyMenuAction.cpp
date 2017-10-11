#include "DependencyMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
DependencyMenuAction::DependencyMenuAction() {
}
DependencyMenuAction::~DependencyMenuAction() {
}
void DependencyMenuAction::MenuPress(LastClass* lastClass) {
	lastClass->classDiagramForm->mouseLButton->ChangeDrawingDependencyState();
}